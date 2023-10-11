package com.example;

public class Exam
{
    private String name = "default_exam_name";
    private int grade = 0;

    public Exam (){}

    public Exam (String name, int grade)
    {
        this.name = name;
        this.grade = grade;
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
