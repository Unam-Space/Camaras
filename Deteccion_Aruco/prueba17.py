import numpy as np
import cv2
import cv2.aruco as aruco
import sys, time, math
import serial
import nums_from_string

# Definimos el numero del marcador a detectar
id_to_find  = 0
marker_size  = 20 #- [cm]


#------------------------------------------------------------------------------
#------- ROTATIONS https://www.learnopencv.com/rotation-matrix-to-euler-angles/
#------------------------------------------------------------------------------
# Checks if a matrix is a valid rotation matrix.
def isRotationMatrix(R):
    Rt = np.transpose(R)
    shouldBeIdentity = np.dot(Rt, R)
    I = np.identity(3, dtype=R.dtype)
    n = np.linalg.norm(I - shouldBeIdentity)
    return n < 1e-6


# Calculates rotation matrix to euler angles
# The result is the same as MATLAB except the order
# of the euler angles ( x and z are swapped ).
def rotationMatrixToEulerAngles(R):
    assert (isRotationMatrix(R))

    sy = math.sqrt(R[0, 0] * R[0, 0] + R[1, 0] * R[1, 0])

    singular = sy < 1e-6

    if not singular:
        x = math.atan2(R[2, 1], R[2, 2])
        y = math.atan2(-R[2, 0], sy)
        z = math.atan2(R[1, 0], R[0, 0])
        

    else:
        x = math.atan2(-R[1, 2], R[1, 1])
        y = math.atan2(-R[2, 0], sy)
        z = 0

    return np.array([x, y, z])

    

	


#Obtenemos las rutas de la calibraciòn de la càmara
calib_path  = ""
camera_matrix   = np.loadtxt(calib_path+'prueba2,1.txt', delimiter=',')
camera_distortion   = np.loadtxt(calib_path+'prueba2,2.txt', delimiter=',')

#--- 180 deg rotation matrix around the x axis
R_flip  = np.zeros((3,3), dtype=np.float32)
R_flip[0,0] = 1.0
R_flip[1,1] =-1.0
R_flip[2,2] =-1.0

#Aqui se definio el diccionario de aruco en donde se modifico para que estos sean de acuerdo a la competencia
aruco_dict  = aruco.getPredefinedDictionary(aruco.DICT_4X4_50)
parameters = aruco.DetectorParameters()


#captura la videocamara y el puerto de comunicaciòn con nuestro arduino
cap = cv2.VideoCapture(0)
ser = serial.Serial('/dev/ttyACM0', 9600)
#Establece el tamaño de la camara con la calibraciòn
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)

#fuente del texto de la imagen 
font = cv2.FONT_HERSHEY_PLAIN

x2 = ''
y2 = ''
z2 = ''

while True:

    #-- Read the camera frame
    ret, frame = cap.read()

    #-- Convert in gray scale
    gray    = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) #-- remember, OpenCV stores color images in Blue, Green, Red

    #-- Find all the aruco markers in the image
    corners, ids, rejected = aruco.detectMarkers(image=gray, dictionary=aruco_dict, parameters=parameters)

    if ids is not None and ids[0] == id_to_find:
        
        #-- ret = [rvec, tvec, ?]
        #-- array of rotation and position of each marker in camera frame
        #-- rvec = [[rvec_1], [rvec_2], ...]    attitude of the marker respect to camera frame
        #-- tvec = [[tvec_1], [tvec_2], ...]    position of the marker in camera frame
        ret = aruco.estimatePoseSingleMarkers(corners, marker_size, camera_matrix, camera_distortion)

        #-- Unpack the output, get only the first
        rvec, tvec = ret[0][0,0,:], ret[1][0,0,:]

        #-- Draw the detected marker and put a reference frame over it
        aruco.drawDetectedMarkers(frame, corners)
        aruco.drawAxis(frame, camera_matrix, camera_distortion, rvec, tvec, 10)
		
        #-- Print the tag position in camera frame
        str_position = "MARKER Position x=%4d y=%4d  z=%4d"%(tvec[0], tvec[1], tvec[2])
        
        #utilizamos una funcion para extraer los datos de nuestra cadena
        marker_position = nums_from_string.get_nums(str_position)
        
        #cada dato extraido de nuestra cadena la convertimos a un string
        strings_position = [str(x) for x in marker_position]
        x = strings_position[0]
        y = strings_position[1]
        z = strings_position[2]
  
        
        vector = [x, y, z]
        print(marker_position)
        print(strings_position)
        print(vector)
        print(type(x))
       
       #enviamos cada dato por nuestro puerto serie 
       
       
       
       
        if x != x2 or y != y2 or z != z2:
       
            if id_to_find == 0:
                ser.write(x.encode())
                ser.write(b',')
                ser.write(y.encode())
                ser.write(b',')
                ser.write(z.encode())
                ser.write(b'\n')
                       
        x2 = x
        y2 = y
        z2 = z            
        
        time.sleep(0.4)
        cv2.putText(frame, str_position, (0, 100), font, 1, (0, 255, 0), 2, cv2.LINE_AA)    
    
   

    #--- Display the frame
    cv2.imshow('frame', frame)

    #--- use 'q' to quit
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        cap.release()
        cv2.destroyAllWindows()
        ser.close()
        break

