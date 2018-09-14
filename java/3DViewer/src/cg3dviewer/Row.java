package cg3dviewer;

import java.awt.Color;
import java.util.Random;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author diegodorta
 */
public class Row {
    
    private String id;
    private String pi;
    private String pj;
    private Color color;

    public Row(String id, String pi, String pj) {
        Random random = new Random();
        
        this.id = id;
        this.pi = pi;
        this.pj = pj;
        this.color = new Color(random.nextInt(256), random.nextInt(256), random.nextInt(256));
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getPi() {
        return pi;
    }

    public void setPi(String pi) {
        this.pi = pi;
    }

    public String getPj() {
        return pj;
    }

    public void setPj(String pj) {
        this.pj = pj;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }
}
