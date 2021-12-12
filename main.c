#include <stdio.h>
#include <math.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
        int flag = 0;
        double maxtrix_3D[8][4] = {           //TODO:Graphic matrix
            {0.4,0.4,0.4,1.0},
            {-0.4,0.4,0.4,1.0},
            {0.4,-0.4,0.4,1.0},
            {0.4,0.4,-0.4,1.0},
            {-0.4,-0.4,0.4,1.0},
            {-0.4,0.4,-0.4,1.0},
            {0.4,-0.4,-0.4,1.0},
            {-0.4,-0.4,-0.4,1.0}
        };

        double maxtrix_tran[4][4] = {         //TODO：translation matrix
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0.3, 0, 0, 1}
        };

        char flag_ro = 'x';                   //TODO:Rotation shaft
#define angle_ro asin(pow(2,1.0/2)/2)  //TODO:Rotation angle [45]


        int flag_sy=4;//1:xoy;2:yoz;3:xoz;4:ox;5:oy;6:oz
//TODO:Axis of symmetry or plane of symmetry

        double maxtrix_zo[4][4] = {           //TODO:Proporation matrix
            {1, 0, 0, 0},
            {0, 0.4, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1.6}
        };

        double                                 //TODO:Fault cut matrix
        d=0.8,g=0.8,                           //X
        b=0,h=0,                               //Y
        c=0,f=0;                               //Z


        double maxtrix_result[8][4];

        double maxtrix_com[8][4] = {           //TODO: matrix
            {0.5,0.5,0.5,1.0},
            {0,0.5,0.5,1.0},
            {0.5,0,0.5,1.0},
            {0.5,0.5,0,1.0},
            {0,0,0.5,1.0},
            {0,0.5,0,1.0},
            {0.5,0,0,1.0},
            {0,0,0,1.0}
        };
        int flag_com=2;                         //1:point 2:line
        int flag_com_detail=1;                  //1:       2:      3:

        double point_x=0;                       //Point:
        double point_y=0.3;
        double point_z=0.4;


        double line_x1=0;                        //Line:
        double line_y1=0;
        double line_z1=0;

        double line_x2=0.3;
        double line_y2=0.3;
        double line_z2=0.3;

#define angle_com_ro asin(pow(2,1.0/2)/2)

#define angle_alpha atan(line_y2-line_y1/line_z2-line_z1)
#define angle_beta atan((line_x2-line_x1)*1.0/(pow(pow(line_y2-line_y1,2)+pow(line_z2-line_z1,2),0.5)))
        void init();
        void display();
        void reshape();
        void mouse();
        void motion();
        void matrixMultiplication(double (*maxtix_1)[4],double (*maxtrix_2)[4]);
        void clearMatrix();
        void drawCoordinate();
        void draw3DModel(double (*maxtrixDraw)[4],float r,float g,float b);
        void translate3DModel(double (*maxtrix1)[4]);
        void rotate3DModle(double (*maxtrix1)[4]);
        void zoom3DModle_1(double (*maxtrix1)[4]);
        void zoom3DModle_2(double (*maxtrix1)[4]);
        void symmetry3DModle(double (*maxtrix1)[4]);
        void shear3DModle(double (*maxtrix1)[4]);
        void compositeTransform(double (*maxtrix1)[4]);
        int main(int args,char* argv[]){
            glutInit(&args,argv);
            init();
            return 0;
        }
        void init(){
            glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
            glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH)/2-400, glutGet(GLUT_SCREEN_HEIGHT)/2-400);
            glutInitWindowSize(800, 800);
            glutCreateWindow("GraphicsTest_4");

            glClear (GL_COLOR_BUFFER_BIT);
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glMatrixMode(GL_PROJECTION);
            glOrtho(-500,500,-500,500,-500,500);


            glutDisplayFunc(display);
            glutReshapeFunc(reshape);
            glutMouseFunc(mouse);
            glutMotionFunc(motion);
            glutMainLoop();
        }
        void display(){                            //TODO:disply
            drawCoordinate();
            draw3DModel(maxtrix_3D,0,1,1);
            translate3DModel(maxtrix_3D);
            zoom3DModle_1(maxtrix_3D);
            rotate3DModle(maxtrix_3D);
            symmetry3DModle(maxtrix_3D);
            shear3DModle(maxtrix_3D);
            compositeTransform(maxtrix_3D);
        }
        void reshape(){

        }
        void mouse(){

        }
        void motion(){

        }
        void matrixMultiplication(double (*maxtix_1)[4],double (*maxtrix_2)[4]){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 4; j++){
                    double sum = 0;
                    for (int m = 0; m < 4; m++){
                        sum+=maxtix_1[i][m]*maxtrix_2[m][j];
                    }
                    maxtrix_result[i][j]=sum;
                }
            }
        }
        void clearMatrix(){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 4; j++) {
                    maxtrix_result[i][j]=0;
                }
            }
        }
        void drawCoordinate(){
            glLoadIdentity();


            glRotated(45,1,0,0);          //Rotate corrdinate
            glRotated(-45,0,1,0);


            glColor3f(1.0f,1.0f,1.0f);


            glLineStipple(2,0x1111);     //Draw dummy line
            glEnable(GL_LINE_STIPPLE);
            glBegin(GL_LINES);
            glVertex3d(0,0,-1);
            glVertex3d(0,0,0);

            glVertex3d(-1,0,0);
            glVertex3d(0,0,0);

            glVertex3d(0,-1,0);
            glVertex3d(0,0,0);
            glEnd();
            glDisable(GL_LINE_STIPPLE);
            glFlush();


            glBegin(GL_LINES);                       //Draw full line
            glVertex3d(0,0,0);
            glVertex3d(0,0,1);

            glVertex3d(0,0,0);
            glVertex3d(1,0,0);

            glVertex3d(0,0,0);
            glVertex3d(0,1,0);
            glEnd();
            glFlush();
        }
        void draw3DModel(double (*maxtrixDraw)[4],float r,float g,float b){
            glLoadIdentity();

            glRotated(45,1,0,0);          //Rotate corrdinate
            glRotated(-45,0,1,0);

            glColor3f(r,g,b);

            printf("The %dth of the matrix transformation:\n",flag);
            for (int i = 0; i < 8; ++i) {
                printf("%f %f %f %f\n",maxtrixDraw[i][0],maxtrixDraw[i][1],maxtrixDraw[i][2],maxtrixDraw[i][3]);
            }
            glBegin(GL_LINE_LOOP);                      //Draw full line

            glVertex3d(maxtrixDraw[0][0],maxtrixDraw[0][1],maxtrixDraw[0][2]);
            glVertex3d(maxtrixDraw[2][0],maxtrixDraw[2][1],maxtrixDraw[2][2]);
            glVertex3d(maxtrixDraw[6][0],maxtrixDraw[6][1],maxtrixDraw[6][2]);
            glVertex3d(maxtrixDraw[3][0],maxtrixDraw[3][1],maxtrixDraw[3][2]);

            glVertex3d(maxtrixDraw[0][0],maxtrixDraw[0][1],maxtrixDraw[0][2]);
            glVertex3d(maxtrixDraw[1][0],maxtrixDraw[1][1],maxtrixDraw[1][2]);
            glVertex3d(maxtrixDraw[5][0],maxtrixDraw[5][1],maxtrixDraw[5][2]);
            glVertex3d(maxtrixDraw[3][0],maxtrixDraw[3][1],maxtrixDraw[3][2]);

            glVertex3d(maxtrixDraw[0][0],maxtrixDraw[0][1],maxtrixDraw[0][2]);
            glVertex3d(maxtrixDraw[1][0],maxtrixDraw[1][1],maxtrixDraw[1][2]);
            glVertex3d(maxtrixDraw[4][0],maxtrixDraw[4][1],maxtrixDraw[4][2]);
            glVertex3d(maxtrixDraw[2][0],maxtrixDraw[2][1],maxtrixDraw[2][2]);

            glEnd();


            glLineStipple(2,0x1111);     //Draw dummy line
            glEnable(GL_LINE_STIPPLE);
            glBegin(GL_LINE_LOOP);

            glVertex3d(maxtrixDraw[7][0],maxtrixDraw[7][1],maxtrixDraw[7][2]);
            glVertex3d(maxtrixDraw[4][0],maxtrixDraw[4][1],maxtrixDraw[4][2]);
            glVertex3d(maxtrixDraw[1][0],maxtrixDraw[1][1],maxtrixDraw[1][2]);
            glVertex3d(maxtrixDraw[5][0],maxtrixDraw[5][1],maxtrixDraw[5][2]);

            glVertex3d(maxtrixDraw[7][0],maxtrixDraw[7][1],maxtrixDraw[7][2]);
            glVertex3d(maxtrixDraw[4][0],maxtrixDraw[4][1],maxtrixDraw[4][2]);
            glVertex3d(maxtrixDraw[2][0],maxtrixDraw[2][1],maxtrixDraw[2][2]);
            glVertex3d(maxtrixDraw[6][0],maxtrixDraw[6][1],maxtrixDraw[6][2]);

            glVertex3d(maxtrixDraw[7][0],maxtrixDraw[7][1],maxtrixDraw[7][2]);
            glVertex3d(maxtrixDraw[5][0],maxtrixDraw[5][1],maxtrixDraw[5][2]);
            glVertex3d(maxtrixDraw[3][0],maxtrixDraw[3][1],maxtrixDraw[3][2]);
            glVertex3d(maxtrixDraw[6][0],maxtrixDraw[6][1],maxtrixDraw[6][2]);

            glEnd();
            glDisable(GL_LINE_STIPPLE);

            flag++;

            glFlush();
        }
        void translate3DModel(double (*maxtrix1)[4]){
            clearMatrix();
            matrixMultiplication(maxtrix1,maxtrix_tran);
            draw3DModel(maxtrix_result,1,0.5f,1);
        }

        void rotate3DModle(double (*maxtrix1)[4]){
            clearMatrix();
            double maxtrix_x[4][4]={
                    {1, 0, 0, 0},
                    {0, cos(angle_ro), sin(angle_ro), 0},
                    {0, -sin(angle_ro), cos(angle_ro), 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_y[4][4]={
                    {cos(angle_ro), 0, -sin(angle_ro), 0},
                    {0, 1, 0, 0},
                    {sin(angle_ro), 0, cos(angle_ro), 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_z[4][4]={
                    {cos(angle_ro), sin(angle_ro), 0, 0},
                    {-sin(angle_ro), cos(angle_ro), 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
            };
            switch (flag_ro) {
                case 'x':
                    matrixMultiplication(maxtrix1,maxtrix_x)
                            ;break;
                case 'y':
                    matrixMultiplication(maxtrix1,maxtrix_y)
                            ;break;
                case 'z':
                    matrixMultiplication(maxtrix1,maxtrix_z)
                            ;break;
                default:
                    printf("ERROR");break;
            }
            draw3DModel(maxtrix_result,1,0,0);
        }
        void zoom3DModle_1(double (*maxtrix1)[4]){
            glLoadIdentity();
            glRotated(45,1,0,0);          //Rotate corrdinate
            glRotated(-45,0,1,0);
            glColor3f(0.0f,1.0f,0.0f);


            glBegin(GL_LINE_LOOP);                  //Draw full line

            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);

            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);

            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);

            glEnd();


            glLineStipple(2,0x1111);     //Draw dummy line
            glEnable(GL_LINE_STIPPLE);
            glBegin(GL_LINE_LOOP);

            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);

            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);

            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(-maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);
            glVertex3d(maxtrix1[0][0]*maxtrix_zo[0][0]*maxtrix_zo[3][3],-maxtrix1[1][1]*maxtrix_zo[1][1]*maxtrix_zo[3][3],-maxtrix1[2][2]*maxtrix_zo[2][2]*maxtrix_zo[3][3]);


            glEnd();
            glDisable(GL_LINE_STIPPLE);
            glFlush();
        }

        void symmetry3DModle(double (*maxtrix1)[4]){
            clearMatrix();
            double maxtrix_xoy[4][4]={
                    {1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, -1, 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_yoz[4][4]={
                    {-1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_xoz[4][4]={
                    {1, 0, 0, 0},
                    {0, -1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_ox[4][4]={
                    {1, 0, 0, 0},
                    {0, -1, 0, 0},
                    {0, 0, -1, 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_oy[4][4]={
                    {-1, 0, 0, 0},
                    {0, 1, 0, 0},
                    {0, 0, -1, 0},
                    {0, 0, 0, 1}
            },
                    maxtrix_oz[4][4]={
                    {1, 0, 0, 0},
                    {0, -1, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}
            };
            switch (flag_sy) {
                case 1:
                    matrixMultiplication(maxtrix1,maxtrix_xoy);
                    break;
                case 2:
                    matrixMultiplication(maxtrix1,maxtrix_yoz);
                    break;
                case 3:
                    matrixMultiplication(maxtrix1,maxtrix_xoz);
                    break;
                case 4:
                    matrixMultiplication(maxtrix1,maxtrix_ox);
                    break;
                case 5:
                    matrixMultiplication(maxtrix1,maxtrix_oy);
                    break;
                case 6:
                    matrixMultiplication(maxtrix1,maxtrix_oz);
                    break;
                default:
                    printf("ERROR");break;
            }
            draw3DModel(maxtrix_result,0.5f,0.5f,0.3f);
        }
        void shear3DModle(double (*maxtrix1)[4]){
            clearMatrix();
            double maxtrix_sh[4][4]={
                    {1, b, c, 0},
                    {d, 1, f, 0},
                    {g, h, 1, 0},
                    {0, 0, 0, 1}
            };
            matrixMultiplication(maxtrix1,maxtrix_sh);
            draw3DModel(maxtrix_result,0,0.25f,1);
        }
        void compositeTransform(double (*maxtrix1)[4]){
            clearMatrix();
            flag=0;
            draw3DModel(maxtrix_com,0,0,1);


            switch (flag_com) {
                case 1:
                    clearMatrix();
                    double maxtrix_com_tran[4][4] = {
                            {1,0,0,0},
                            {0,1,0,0},
                            {0,0,1,0},
                            {-point_x,-point_y,-point_z,1}
                    };
                    double maxtrix_com_opp_tran[4][4] = {
                            {1,0,0,0},
                            {0,1,0,0},
                            {0,0,1,0},
                            {point_x,point_y,point_z,1}
                    };
                    switch (flag_com_detail) {
                        case 1:
                            clearMatrix();
                            matrixMultiplication(maxtrix_com,maxtrix_com_tran);
                            matrixMultiplication(maxtrix_result,maxtrix_zo);
                            matrixMultiplication(maxtrix_result,maxtrix_com_opp_tran);
                            draw3DModel(maxtrix_result,1,1,0);
                            break;
                        case 2:
                            clearMatrix();
                            double maxtrix_x[4][4]={
                                    {1, 0, 0, 0},
                                    {0, cos(angle_ro), sin(angle_ro), 0},
                                    {0, -sin(angle_ro), cos(angle_ro), 0},
                                    {0, 0, 0, 1}
                            },
                                    maxtrix_y[4][4]={
                                    {cos(angle_ro), 0, -sin(angle_ro), 0},
                                    {0, 1, 0, 0},
                                    {sin(angle_ro), 0, cos(angle_ro), 0},
                                    {0, 0, 0, 1}
                            },
                                    maxtrix_z[4][4]={
                                    {cos(angle_ro), sin(angle_ro), 0, 0},
                                    {-sin(angle_ro), cos(angle_ro), 0, 0},
                                    {0, 0, 1, 0},
                                    {0, 0, 0, 1}
                            };
                            matrixMultiplication(maxtrix_com,maxtrix_com_tran);
                            switch (flag_ro) {
                                case 'x':
                                    matrixMultiplication(maxtrix_result,maxtrix_x)
                                            ;break;
                                case 'y':
                                    matrixMultiplication(maxtrix_result,maxtrix_y)
                                            ;break;
                                case 'z':
                                    matrixMultiplication(maxtrix_result,maxtrix_z)
                                            ;break;
                                default:
                                    printf("ERROR");break;
                            }
                            matrixMultiplication(maxtrix_result,maxtrix_com_opp_tran);
                            draw3DModel(maxtrix_result,1,0,0);
                            break;
                        case 3:
                            clearMatrix();
                            double maxtrix_sh[4][4]={
                                    {1, b, c, 0},
                                    {d, 1, f, 0},
                                    {g, h, 1, 0},
                                    {0, 0, 0, 1}
                            };
                            matrixMultiplication(maxtrix_com,maxtrix_com_tran);
                            matrixMultiplication(maxtrix_result,maxtrix_sh);
                            matrixMultiplication(maxtrix_result,maxtrix_com_opp_tran);
                            draw3DModel(maxtrix_result,0,0.25f,1);
                            break;
                        default:
                            printf("ERROR.");
                            break;
                    }
                    break;
                case 2:
                    clearMatrix();
                    double maxtrix_com_ta[4][4] = {
                            {1,0,0,0},
                            {0,1,0,0},
                            {0,0,1,0},
                            {-line_x1,-line_y1,-line_z1,1}
                    };
                    line_x1=0,line_y1=0,line_z1=0;
                    line_x2-=line_x1;
                    line_y2-=line_y1;
                    line_z2-=line_z1;

                    double v= pow(pow(line_y2,2)+ pow(line_z2,2),1.0/2);
                    line_y2=0;
                    line_z2=v;
                    double maxtrix_com_rx[4][4] = {
                            {1,0,0 ,0},
                            {0,cos(angle_alpha), sin(angle_alpha),0},
                            {0,-sin(angle_alpha), cos(angle_alpha),0},
                            {0,0,0,1}
                    };
                    double maxtrix_com_ry[4][4] = {
                            {cos(-angle_beta),0,-sin(-angle_beta),0},
                            {0,1, 0,0},
                            {sin(-angle_beta),0, cos(-angle_beta),0},
                            {0,0,0,1}
                    };
                    double maxtrix_com_z[4][4]={
                            {cos(angle_com_ro), sin(angle_com_ro), 0, 0},
                            {-sin(angle_com_ro), cos(angle_com_ro), 0, 0},
                            {0, 0, 1, 0},
                            {0, 0, 0, 1}
                    };
                    double maxtrix_com_ry_opp[4][4] = {
                            {cos(angle_beta),0,-sin(angle_beta),0},
                            {0,1, 0,0},
                            {sin(angle_beta),0, cos(angle_beta),0},
                            {0,0,0,1}
                    };
                    double maxtrix_com_rx_opp[4][4] = {
                            {1,0,0 ,0},
                            {0,cos(-angle_alpha), sin(-angle_alpha),0},
                            {0,-sin(-angle_alpha), cos(-angle_alpha),0},
                            {0,0,0,1}
                    };
                    double maxtrix_com_ta_opp[4][4] = {
                            {1,0,0,0},
                            {0,1,0,0},
                            {0,0,1,0},
                            {line_x1,line_y1,line_z1,1}
                    };
                    matrixMultiplication(maxtrix_com,maxtrix_com_ta);
                    draw3DModel(maxtrix_result,1,0,0);
                    matrixMultiplication(maxtrix_result,maxtrix_com_rx);

                    matrixMultiplication(maxtrix_result,maxtrix_com_ry);

                    matrixMultiplication(maxtrix_result,maxtrix_com_z);

                    matrixMultiplication(maxtrix_result,maxtrix_com_ry_opp);

                    matrixMultiplication(maxtrix_result,maxtrix_com_rx_opp);

                    matrixMultiplication(maxtrix_result,maxtrix_com_ta_opp);
                    draw3DModel(maxtrix_result,1,0,0.35f);
                default:
                    printf("ERROR.");
                    break;
            }
        }