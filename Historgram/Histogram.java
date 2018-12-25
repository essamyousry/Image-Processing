import java.util.Scanner;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;

public class Histogram{
  public static void main(String [] args){

      File inFile = new File (args[0]);
      File outFile = new File (args[1]);

      computeHistogram(inFile, outFile);

  }
  public static void computeHistogram(File in, File out){

    int row, col, min, max;
    int [] vars = new int [4];
      
      try {

          Scanner sc = new Scanner(in);

          int c = 0;
            while (sc.hasNextInt() && c != 4){
                vars[c++] = sc.nextInt();
            }

            row = vars[0];
            col = vars[1];
            min = vars[2];
            max = vars[3];

          System.out.println(row);
          System.out.println(col);
          System.out.println(min);
          System.out.println(max);
          
            int [][] data = new int [row][col];
            int [] hist = new int [max + 1];

            for (int i = 0; i < row; i++){
              for (int j = 0; j < col; j++){
                data[i][j] = sc.nextInt();
              }
            }
          
          for (int x = 0; x <= max; x++){
              int count = 0;
              for (int i = 0; i < row; i++){
                  for (int j = 0; j < col; j++){
                      if (data[i][j] == x) count++;
                  }
              }
              hist[x] = count;
          }
          
          PrintWriter pw = new PrintWriter(new FileWriter(out));
          pw.print(row);
          pw.print(' ');
          pw.print(col);
          pw.print(' ');
          pw.print(min);
          pw.print(' ');
          pw.print(max);
          pw.println();
          
          for (int i = 0; i <= max; i++){
              pw.print(i);
              pw.print(' ');
              pw.print(' ');
              pw.print(hist[i]);
              pw.println();
          }
          pw.close();
       
      }
      catch (Exception e) {
          System.out.println("Error " + e);
      }
    }
}
