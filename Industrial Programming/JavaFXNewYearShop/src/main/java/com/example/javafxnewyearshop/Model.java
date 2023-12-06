package com.example.javafxnewyearshop;

import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

import java.sql.*;

public class Model
{
    private final String URL = "jdbc:mysql://localhost:3306/mydbtest";
    private final String USERNAME = "root";
    private final String PASSWORD = "root";

    private void readBD()
    {
        try
        {
            //Class.forName("org.mysql.JDBC");
            Connection connection = DriverManager.getConnection(URL, USERNAME, PASSWORD);
            System.out.println("DataBase connection successful!");

            Statement statement = connection.createStatement();
            ResultSet rs = statement.executeQuery("SELECT concert_price FROM mydbtest.program;");

            while(rs.next())
            {
                concertPrice = rs.getInt("concert_price");
            }

            rs = statement.executeQuery("SELECT name FROM mydbtest.manufacturer where program_id = 1;");

            nameList = new ArrayList<>();
            while(rs.next())
            {
                nameList.add(rs.getString("name"));
            }
            manufactureAmount = nameList.size();

            manufactureList = new ArrayList<>();
            for(int i = 0; i < manufactureAmount; i++)
            {
                rs = statement.executeQuery("SELECT * FROM mydbtest.product where manufacturer_id = " + Integer.toString(i + 1) + ";");

                Manufacturer m = new Manufacturer(nameList.get(i), rs);
                manufactureList.add(m);
            }

            connection.close();
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
            System.out.println("bobo ");
        }
    }

    private int manufactureAmount;
    private ArrayList<Manufacturer> manufactureList;
    public ArrayList<String> nameList;
    private int concertPrice;
    private int manufactureChose = 0;
    private boolean concertChosen = false;
    private boolean isRegular = false;

    public Model()
    {
        //read();
        readBD(); //reads completely from a database. A full replacement to the read from txt method
        nameList = new ArrayList<>();
        for(int i = 0; i < manufactureAmount; i++)
        {
            nameList.add(manufactureList.get(i).name);
        }
    }

    private void read()
    {
        try
        {
            File file = new File("input.txt");
            Scanner scanner = new Scanner(file);
            manufactureAmount = Integer.parseInt(scanner.nextLine());
            concertPrice = Integer.parseInt(scanner.nextLine());
            manufactureList = new ArrayList<>();
            for(int i = 0; i < manufactureAmount; i++)
            {
                Manufacturer m = new Manufacturer(scanner);
                manufactureList.add(m);
            }
        }
        catch (Exception e)
        {
            System.out.println("An error occured while reading from a file.");
            e.printStackTrace();
        }
    }

    public void setManufactureChose(int manufactureChose) {
        this.manufactureChose = manufactureChose;
    }

    public void setConcertChosen(boolean isChosen) {
        concertChosen = isChosen;
    }

    public void setIsRegular(boolean isRegular) {
        this.isRegular = isRegular;
    }

    public void setItemOn(int number)
    {
        manufactureList.get(manufactureChose).list.get(number).setMarked(true);
    }

    public void setItemOff(int number)
    {
        manufactureList.get(manufactureChose).list.get(number).setMarked(false);
    }

    private void clearItems()
    {
        manufactureList.get(manufactureChose).clearAll();
    }

    public float price()
    {
        float p = 0;
        p += (float) manufactureList.get(manufactureChose).getPriceOverall();

        if(concertChosen)
        {
            p += (float)concertPrice;
        }

        if(isRegular)
        {
            p *= 0.9f;
        }
        return p;
    }

    public int getManufactureAmount() {
        return manufactureAmount;
    }

    public ArrayList<Manufacturer> getManufactureList() {
        return manufactureList;
    }

    public int getCurrentAmount()
    {
        return manufactureList.get(manufactureChose).list.size();
    }

    public void setChosenProduct(String pName)
    {

        manufactureList.get(manufactureChose).setChosenProduct(pName);

    }
}
