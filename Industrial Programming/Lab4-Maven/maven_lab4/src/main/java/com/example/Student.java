package com.example;

public class Student {
    private String name;
    private String surname;
    private String patronimic;
    private int age;

    public Student()
    {
        name = "defaut_name";
        surname = "default_surname";
        patronimic = "default_patronimic";
        age = 0;
    }

    public Student(String name, String surname, String patronimic, int age)
    {
        this.name = name;
        this.surname = surname;
        this.patronimic = patronimic;
        this.age = age;
    }

    public Student(Student other)
    {
        this.setName(other.getName());
        this.setSurname(other.getSurname());
        this.setPatronimic(other.getPatronimic());
        this.setAge(other.getAge());
    }

    public String getName()
    {
        return name;
    }

    public void setName(String name)
    {
        if(!name.isEmpty())
        {
            this.name = name;
        }
    }

    public String getSurname()
    {
        return surname;
    }

    public void setSurname(String surname)
    {
        if(!surname.isEmpty())
        {
            this.surname = surname;
        }
    }

    public String getPatronimic()
    {
        return patronimic;
    }

    public void setPatronimic(String patronimic)
    {
        if(!patronimic.isEmpty())
        {
            this.patronimic = patronimic;
        }
    }

    public int getAge()
    {
        return age;
    }

    public void setAge(int age)
    {
        if(age >= 0)
        {
            this.age = age;
        }
    }

    @Override
    public String toString()
    {
        return "Student{" +
                "name='" + name + '\'' +
                ", surname=" + surname + '\'' +
                ", patronimic=" + patronimic + '\'' +
                ", age=" + age +
                '}';
    }
}
