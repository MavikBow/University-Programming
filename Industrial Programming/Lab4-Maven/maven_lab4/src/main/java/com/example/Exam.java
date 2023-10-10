package com.example;

public class Exam
{
    private String name = "default_exam_name";
    private int grade = 0;

    public Exam (String n, int g)
    {
        name = n;
        grade = g;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getGrade() {
        return grade;
    }

    public void setGrade(int grade) {
        this.grade = grade;
    }

    @Override
    public String toString() {
        return "Exam{" +
                "name='" + name + '\'' +
                ", grade=" + grade +
                '}';
    }
}
