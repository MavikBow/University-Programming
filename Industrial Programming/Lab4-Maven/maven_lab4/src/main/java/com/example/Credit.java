package com.example;

public class Credit
{
    private String name = "default_exam_name";
    private boolean pass = false;

    public Credit (){}

    public Credit (String name, boolean pass)
    {
        this.name = name;
        this.pass = pass;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean getGrade() {
        return pass;
    }

    public void setGrade(boolean pass) {
        this.pass = pass;
    }

    @Override
    public String toString() {
        return "Exam{" +
                "name='" + name + '\'' +
                ", pass=" + pass +
                '}';
    }
}
