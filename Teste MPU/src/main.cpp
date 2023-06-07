// Programa: Teste MPU6050
#include <Arduino.h>
#include <Wire.h>
// Endereco I2C do MPU6050
const int MPU = 0x68;
// Variaveis para armazenar valores dos sensores
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  // Inicializa o MPU -6050
  Wire.write(0);
  Wire.endTransmission(1);
}
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // starting with register 0 x3B ( ACCEL_XOUT_H )
  Wire.endTransmission(0);
  // Solicita os dados do sensor
  Wire.requestFrom(MPU, 14, 1);
  // Armazena o valor dos sensores nas variaveis correspondentes
  AcX = Wire.read() << 8 | Wire.read(); // 0 x3B ( ACCEL_XOUT_H ) & 0 x3C ( ACCEL_XOUT_L )
  AcY = Wire.read() << 8 | Wire.read(); // 0 x3D ( ACCEL_YOUT_H ) & 0 x3E ( ACCEL_YOUT_L )
  AcZ = Wire.read() << 8 | Wire.read(); // 0 x3F ( ACCEL_ZOUT_H ) & 0 x40 ( ACCEL_ZOUT_L )
  Tmp = Wire.read() << 8 | Wire.read(); // 0 x41 ( TEMP_OUT_H ) & 0x42 ( TEMP_OUT_L )
  GyX = Wire.read() << 8 | Wire.read(); // 0 x43 ( GYRO_XOUT_H ) & 0 x44 ( GYRO_XOUT_L )
  GyY = Wire.read() << 8 | Wire.read(); // 0 x45 ( GYRO_YOUT_H ) & 0 x46 ( GYRO_YOUT_L )
  GyZ = Wire.read() << 8 | Wire.read(); // 0 x47 ( GYRO_ZOUT_H ) & 0 x48 ( GYRO_ZOUT_L )
  Serial.print(" AcX = ");
  Serial.print(AcX);
  Serial.print(" | AcY = ");
  Serial.print(AcY);
  Serial.print(" | AcZ = ");
  Serial.print(AcZ);
  Serial.print(" | Tmp = ");
  Serial.print(Tmp / 340.00 + 36.53);
  Serial.print(" | GyX = ");
  Serial.print(GyX);
  Serial.print(" | GyY = ");
  Serial.print(GyY);
  Serial.print(" | GyZ = ");
  Serial.println(GyZ);
  // Aguarda 300 ms e reinicia o processo
  delay(300);
}