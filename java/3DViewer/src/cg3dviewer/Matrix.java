/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package cg3dviewer;

/**
 *
 * @author diegodorta
 */
public class Matrix {
    
    // Ponto que sera transformado
    double point[][] = new double[1][4];
 
    //Ponto que sera transformado
    public double[][] getPoint() {
        return point;
    }

    public void setPoint(double x, double y, double z) {               
        this.point[0][0] = x;
        this.point[0][1] = y;
        this.point[0][2] = z;
        this.point[0][3] = 1;
    }
    
    //Matriz de Traslação
    public double[][] translationMatrix(double tx, double ty, double tz) {
        double matrix[][] = new double[4][4];
        
        matrix[0][0] = 1;
        matrix[0][1] = 0;
        matrix[0][2] = 0;
        matrix[0][3] = 0;

        matrix[1][0] = 0;
        matrix[1][1] = 1;
        matrix[1][2] = 0;
        matrix[1][3] = 0;

        matrix[2][0] = 0;
        matrix[2][1] = 0;
        matrix[2][2] = 1;
        matrix[2][3] = 0;

        matrix[3][0] = -tx;
        matrix[3][1] = -ty;
        matrix[3][2] = -tz;
        matrix[3][3] = 1;
        
        return matrix;
    }

    //Matriz de Rotação em torno do eixo X
    public double[][] rotationMatrixX(double sen, double cos) {
        double matrix[][] = new double[4][4];
        
        matrix[0][0] = 1;
        matrix[0][1] = 0;
        matrix[0][2] = 0;
        matrix[0][3] = 0;

        matrix[1][0] = 0;
        matrix[1][1] = cos;
        matrix[1][2] = -sen;
        matrix[1][3] = 0;

        matrix[2][0] = 0;
        matrix[2][1] = sen;
        matrix[2][2] = cos;
        matrix[2][3] = 0;

        matrix[3][0] = 0;
        matrix[3][1] = 0;
        matrix[3][2] = 0;
        matrix[3][3] = 1;
        
        return matrix;
    }

    //Matriz de Rotação em torno do eixo Y
    public double[][] rotationMatrixY(double sen, double cos) {
        double matrix[][] = new double[4][4];
        
        matrix[0][0] = cos;
        matrix[0][1] = 0;
        matrix[0][2] = sen;
        matrix[0][3] = 0;

        matrix[1][0] = 0;
        matrix[1][1] = 1;
        matrix[1][2] = 0;
        matrix[1][3] = 0;

        matrix[2][0] = -sen;
        matrix[2][1] = 0;
        matrix[2][2] = cos;
        matrix[2][3] = 0;

        matrix[3][0] = 0;
        matrix[3][1] = 0;
        matrix[3][2] = 0;
        matrix[3][3] = 1;
        
        return matrix;
    }
    
    //Matriz de Rotação em torno do eixo Z
    public double[][] rotationMatrixZ(double sen, double cos) {
        double matrix[][] = new double[4][4];
        
        matrix[0][0] = cos;
        matrix[0][1] = -sen;
        matrix[0][2] = 0;
        matrix[0][3] = 0;

        matrix[1][0] = sen;
        matrix[1][1] = cos;
        matrix[1][2] = 0;
        matrix[1][3] = 0;

        matrix[2][0] = 0;
        matrix[2][1] = 0;
        matrix[2][2] = 1;
        matrix[2][3] = 0;

        matrix[3][0] = 0;
        matrix[3][1] = 0;
        matrix[3][2] = 0;
        matrix[3][3] = 1;
        
        return matrix;
    }
    
    // Matriz de mudança de escala
    public double[][] scaleMatrix(double Sx, double Sy, double Sz) {
        double matrix[][] = new double[4][4];
        
        matrix[0][0] = Sx;
        matrix[0][1] = 0;
        matrix[0][2] = 0;
        matrix[0][3] = 0;

        matrix[1][0] = 0;
        matrix[1][1] = Sy;
        matrix[1][2] = 0;
        matrix[1][3] = 0;

        matrix[2][0] = 0;
        matrix[2][1] = 0;
        matrix[2][2] = Sz;
        matrix[2][3] = 0;

        matrix[3][0] = 0;
        matrix[3][1] = 0;
        matrix[3][2] = 0;
        matrix[3][3] = 1;
        
        return matrix;
    }
    
    // Matriz de clipping
    public double[][] clippingMatrix(double d, double s) {
        double matrix[][] = new double[4][4];
        
        matrix[0][0] = d/s;
        matrix[0][1] = 0;
        matrix[0][2] = 0;
        matrix[0][3] = 0;

        matrix[1][0] = 0;
        matrix[1][1] = d/s;
        matrix[1][2] = 0;
        matrix[1][3] = 0;

        matrix[2][0] = 0;
        matrix[2][1] = 0;
        matrix[2][2] = 1;
        matrix[2][3] = 0;

        matrix[3][0] = 0;
        matrix[3][1] = 0;
        matrix[3][2] = 0;
        matrix[3][3] = 1;
        
        return matrix;
    }
}
