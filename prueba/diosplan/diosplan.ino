String vectorString;
int list[3];

void setup() 
{
  Serial.begin(19200); //Checar si un valor mayor aumenta la pecisión y/o disminuye los errores
}

int i, value, counter = 0;
int vectorLength;
String tempString = "####";

void loop() 
{
  if(!Serial.available())
    return;

  vectorString = Serial.readString(); 
  Serial.print(vectorString);
  //vectorLength = vectorString.length() - 2; //Por alguna razón, suma el valor de la cadena +2

  if(vectorString[0] != '[')
    return;

  for(i = 1; i < vectorString.length() - 3; i++) //Recorre toda la cadena, char por char
  {   
    if((vectorString[i+1] == ']') || (vectorString[i+1] == ','))
    {
      tempString[0] = vectorString[i];
      i += 1;
    }
    else if((vectorString[i+2] == ']') || (vectorString[i+2] == ','))
    {
      tempString[0] = vectorString[i];
      tempString[1] = vectorString[i+1];
      i += 2;
    }
    else if((vectorString[i+3] == ']') || (vectorString[i+3] == ','))//Revisar
    {
      tempString[0] = vectorString[i];
      tempString[1] = vectorString[i+1];
      tempString[2] = vectorString[i+2];
      i += 3;
    }
    else if((vectorString[i+4] == ']') || (vectorString[i+4] == ','))//Revisar
    {
      tempString[0] = vectorString[i];
      tempString[1] = vectorString[i+1];
      tempString[2] = vectorString[i+2];
      tempString[3] = vectorString[i+3];
      i += 4;
    }

    value = tempString.toInt();
    tempString = "####"; //Reset string
    list[counter] = value;
    counter++;
    if(counter == 3)
      counter = 0;
  }
  Serial.print("List[0]: ");
  Serial.println(list[0]);
  Serial.print("List[1]: ");
  Serial.println(list[1]);
  Serial.print("List[2]: ");
  Serial.println(list[2]);
}
