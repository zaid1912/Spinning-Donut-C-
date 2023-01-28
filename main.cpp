#include<iostream>
#include<math.h>
#include <unistd.h>
#define width 60
#define height 60

using namespace std;
#define pi 3.142

 class donut{
    private:
    float A, B, theta, phi; 
    const float thetaIncrement, phiIncrement, r1, r2, k2;
    char resol[height][width];
    float z_buf[height][width];
    int k1;
    public:
    donut(): thetaIncrement(0.07), phiIncrement(0.02), r2(2), r1(1), k2(7){
        A=0; 
        B=0;
        k1 = 1;

    }
    void createDonut(){
        while(1){
          for(int i = 0; i <height; i++){
            for(int j = 0; j<width; j++){
              resol[i][j] = ' ';
              z_buf[i][j] = 0;
            }
          }
          
            for(theta = 0; theta < 2*pi; theta+=thetaIncrement){
                for(phi = 0; phi < 2*pi; phi+=phiIncrement){
                    float sinphi = sin(phi);
                    float cosphi = cos(phi);
                    float sintheta = sin(theta);
                    float costheta = cos(theta);
                    float sinA = sin(A);
                    float sinB = sin(B);
                    float cosA = cos(A);
                    float cosB = cos(B);
                    float xComp = r2 + r1*costheta;
                    float yComp = r1*sintheta;
                    float z =  sinphi * xComp * sinA + sintheta * cosA;
                    float xyPrime = 1/(z + k2);
                    
                    int x = 35 + 25 * xyPrime * (cosphi * xComp * cosB - (sinphi * xComp * cosA - sintheta * sinA) * sinB); 
                    int y = 30 + 50 * xyPrime * (cosphi * xComp * sinB + (sinphi * xComp * cosA - sintheta * sinA)* cosB); 
                    
                    
                    int luminance = 8*(cosphi*costheta*sinB - cosA*costheta*sinphi- sinA*sintheta + cosB*(cosA*sinB - costheta*sinA));
                    if (x < width && x > 0 && y > 0 && y<height && xyPrime > z_buf[x][y])
                    {
                        z_buf[x][y] = xyPrime;

                        // Choosing ASCII character based on Luminance and storing it in z_buf(buffer)
                        resol[x][y] = ".,-~:;=!*#$@"[luminance > 0 ? luminance : 0];
                    }



                }
        }
       
        system("clear");
        
        for(int i = 0; i<height; i++){
          for(int j = 0; j<width; j++){
            cout<<(char)(resol[i][j]);
          }
          cout<<endl;
        }
        A += 0.3;
        B += 0.3;
        usleep(40000);

    }
    }
 };

 int main(){
     donut D;
     D.createDonut();
 }