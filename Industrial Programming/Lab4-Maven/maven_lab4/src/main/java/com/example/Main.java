package com.example;

import java.io.IOException;

import com.fasterxml.jackson.databind.ObjectMapper;

public class Main 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );

        Exam exam = new Exam("Matan", 10);

        ObjectMapper objectMapper = new ObjectMapper();
        String json = new String();
        
        try
        {
            json = objectMapper.writeValueAsString(exam);
            System.out.println(json);
        }
        catch (IOException e)
        {
            System.out.println("An error occurred while converting object to JSON: " + e.getMessage());
        }

        try
        {
            Exam examNew = objectMapper.readValue(json, Exam.class);
            System.out.println(examNew);
        }
        catch (Exception e)
        {
            System.out.println(e.getMessage());
        }


        System.exit(0);
    }
}
