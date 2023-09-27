import java.io.*;
import java.nio.charset.StandardCharsets;

public class Main
{
    static Card[] card = new Card[20];

    public static void input()
    {
        try
        {
            InputStream is = new FileInputStream("input.txt");
            InputStreamReader file = new InputStreamReader(is, StandardCharsets.UTF_8);
            BufferedReader br = new BufferedReader(file);
            
            for (int i = 0; i < 20; i++)
            {

                String FIO = br.readLine();
                String[] words = FIO.split("\\s+");

                String name = words[0];
                String surname = words[1];
                String patronimic = words[2];

                int year = Integer.parseInt(words[3]);
                int group = Integer.parseInt(words[4]);
                int session_number = Integer.parseInt(words[5]);
            
                card[i] = new Card(surname, name, patronimic, year, group, session_number);

                for(int j = 0; j < 5; j++)
                {
                    String S = br.readLine();
                    String[] words2 = S.split("\\s+");

                    card[i].addSession(words2[0], Integer.parseInt(words2[1]), Integer.parseInt(words2[2]));
                }
            }

            br.close();
            file.close();
            is.close();
        }
        catch (Exception e)
        {
            System.out.println("Can't open input file");
        }
    }

    public static void output()
    {
        try
        {
            OutputStream os = new FileOutputStream("output.txt");
            OutputStreamWriter osr = new OutputStreamWriter(os, "UTF-8");
		    BufferedWriter bw = new BufferedWriter(osr);

            for(int i = 0; i < 20; i++)
            {
                bw.write(card[i].output());
            }

            bw.close();
            osr.close();
            os.close();
        }
        catch (Exception e)
        {
            System.out.println("Couldn't open output file");
        }
    }
    public static void main(String[] args)
    {
        input();
        output();
    }
}