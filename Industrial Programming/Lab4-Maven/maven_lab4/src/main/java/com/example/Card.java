package com.example;

public class Card
{
    private Student student = new Student();
    private int year = 0;
    private int group = 0;
    private int ID;

    public Card(){}

    public Card(Student student, int year, int group)
    {
        this.student = new Student(student);
        this.year = year;
        this.group = group;
    }
}
