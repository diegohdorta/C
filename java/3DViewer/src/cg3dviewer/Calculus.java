package cg3dviewer;

public class Calculus {
    
    public Calculus() {
        
    }
    
    /*Multiplicação de matriz 4x4*/
    public double[][] matrix4x4Multiplies(double mA[][], double mB[][]) {
        int row, col, i;
        double aux;
        double c[][] = new double[mA.length][mB[0].length];
        
        for (row = 0; row < c.length; row++) {
            for (col = 0; col < c[row].length; col++) {
                aux = 0;
                for (i = 0; i < mA[row].length; i++) {
                    aux = aux + mA[row][i] * mB[i][col];
                }
                c[row][col] = aux;
            }
        }
        return c;
    }
    
    public double hypotenuse(double x, double y) {
        double hypotenuse;
        
        hypotenuse = Math.sqrt((x * x) + (y * y));
        return hypotenuse;
    }

    public double getSenCos(double val, double hypotenuse) {
        return (val / hypotenuse);
    }   
    
    public double getXs( double xc, double zc, double vsx, double vcx) {
        double xs = 0;
        
        xs = ((xc / zc) * vsx) + vcx;
        return xs;
    }
    
    public double getYs( double yc, double zc, double vsy, double vcy) {
        double ys = 0;
        
        ys = ((yc / zc) * vsy) + vcy;
        return ys;
    }
}
