
bool oldControlValues[4]={};
void sendControle(){
  for(int i=0;i<3;i++){
    bool state_i=!digitalRead(i+3);
    if(state_i!=oldControlValues[i]){
      Serial.write(0xB0);
      Serial.write(0x14+i);
      Serial.write(state_i==1?0x7F:0x00);
    }oldControlValues[i]=state_i;
  }
}
