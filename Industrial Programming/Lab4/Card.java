import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;

class Card
{
    private String name = "default";
    private String surname = "default";
    private String patronimic= "default";

    private int year = 0;
    private int group = 0;

    private int session_number = 0;

    private List<Session> session;

    public Card(){}

    public Card(String n, String s, String p, int y, int g, int s_n)
    {
        name = n;
        surname = s;
        patronimic = p;
        year = y;
        group = g;

        session_number = s_n;
        
        session = new ArrayList<>();
    }

    public void addSession(String subject, int exam_credit, int grade)
    {
        session.add(new Session(subject, exam_credit, grade));
    }

    public boolean isExcellent()
    {
        boolean result = true;

        for (Session s : session) {
            result &= s.isExcellent();
        }

        return result;
    }

    private void input(BufferedReader br)
    {
        try
        {
            String FIO = br.readLine();
            String[] words = FIO.split("\\s+");

            surname = words[0];
            name = words[1];
            patronimic = words[2];

            year = Integer.parseInt(words[3]);
            group = Integer.parseInt(words[4]);
            session_number = Integer.parseInt(words[5]);

            session = new ArrayList<>();
        
            for(int i = 0; i < 5; i++)
            {
                String S = br.readLine();
                String[] words2 = S.split("\\s+");

                addSession(words2[0], Integer.parseInt(words2[1]), Integer.parseInt(words2[2]));
            }
        }
        catch (Exception e)
        {
            System.out.println("trouble reading the file");
        }
    }

    public String output()
    {
        String data = "";

        if (isExcellent())
        {
            data = surname + " " + name + " " + patronimic + " - " + Integer.toString(year) + " курс, " + Integer.toString(group) + " группа, " + Integer.toString(session_number) + " сессия:\n";

            for (Session s : session) 
            {
                data += s.sessionData() + '\n';
            }
        }

        return data;
    }

    private class Session
    {
        private String subject;
        private boolean exam_credit;
        private int grade;
        private boolean pass;

        private Session(String s, int e_c, int g)
        {
            subject = s;

            if (e_c == 1) exam_credit = true;
            else exam_credit = false;

            grade = g;

            if (grade >= 4)
            {
                pass = true;
            }
            else
            {
                pass = false;
            }
        }

        private boolean isExcellent()
        {
            boolean excellent = true;

            if (exam_credit && grade < 9)
            {
                excellent = false;
            }

            if (!exam_credit && grade < 4)
            {
                excellent = false;
            }

            return excellent;
        }

        private String sessionData()
        {
            String data = subject + ": ";

            if(exam_credit)
            {
                data += Integer.toString(grade);
            }
            else
            {
                if (pass)
                {
                    data += "зачёт";
                }
                else
                {
                    data += "не зачёт";
                }
            }

            return data;
        }
    }
}
