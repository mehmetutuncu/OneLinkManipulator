    #include <I2Cdev.h> //I2C kütüphanesini ekledik
    #include <MPU6050.h> //Mpu6050 kütüphanesi ekledik
    #include <LiquidCrystal.h>
    #include <Servo.h>
    #include<Wire.h>
    const int MPU=0x68;  // I2C address of the MPU-6050
    Servo servo;
    int sayac = 0;
    int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
    void setup(){
       servo.attach(9); //8 nolu pini servo için atandı.
      servo.write(0); // 0 dereceye atar servo motoru
      servoCalistir();
      Wire.begin();
      Wire.beginTransmission(MPU);
      Wire.write(0x6B);  // PWR_MGMT_1 register
      Wire.write(0);     // İvme sensörünü uyandırır/aktif eder.
      Wire.endTransmission(true);
      Serial.begin(9600);
      Serial.println("CLEARDATA");
      Serial.println("LABEL,Titresim Orani"); //Makro ile alacağımız kısım.
     
    }
    void servoCalistir(){
       servo.write(90); // servo motoru 90 dereceye ayarlar.
       delay(2000);    //2sn bekledikten sonra alt satıra iner.
       servo.write(0);   // Servo motora 0 derece ayarlandı.
    }
    void loop(){
      
      if(sayac < 20 ){
           Wire.beginTransmission(MPU);
      Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
      Wire.endTransmission(false);
      Wire.requestFrom(MPU,14,true);  // request a total of 14 registers
      AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
      //Serial.print("AcX = "); Serial.println(AcX);
      Serial.print("DATA,"); Serial.println(AcY);
      delay(500);
      sayac++;
       }
    }




    
     /* AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
      Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
      GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
      GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
      GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
       AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
      * Serial.print(" | AcZ = "); Serial.print(AcZ);
      Serial.print(" | Tmp = "); Serial.print((Tmp / 340. + 36.53) * 1.8 + 32);  //equation for temperature in degrees C from datasheet
      Serial.print(" | GyX = "); Serial.print(GyX);
      Serial.print(" | GyY = "); Serial.print(GyY);
      Serial.print(" | GyZ = "); Serial.println(GyZ);*/

