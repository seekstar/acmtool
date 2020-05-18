import java.util.*;
import java.math.*;
//import java.lang.Character;

public class Main {		//Need be modified to ¡°Main¡± before submission
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String str = in.next();
        int len = str.length();
        BigInteger a;
        int arr[];
        try
        {
            arr = Translate(str.toCharArray(), len);
        }catch(Exception e)
        {
            System.out.println(e);
            return;
        }
        
        try
        {
            a = RadixConvert(arr, len, 36);
        }
        catch(Exception e)
        {
            System.out.println(e);
            return;
        }
        System.out.println(a);
    }
    
    /**
     *
     * @param str
     * @param len
     * @return 
     * @throws java.lang.Exception
     */
    public static int[] Translate(char str[], int len) throws Exception
    {
        int arr[] = new int[len];
        for(int i = 0; i < len; ++i)
        {
            try
            {
                arr[i] = Translate(str[i]);
            }
            catch(Exception e)
                    {
                        throw e;
                    }
        }
        return arr;
    }
    
    /**
     *
     * @param ch
     * @return
     * @throws Exception
     */
    public static int Translate(char ch) throws Exception
    {
        if(Character.isDigit(ch))
        {
            return ch - '0';
        }
        else if(Character.isUpperCase(ch))
        {
            return ch - 'A' + 10;
        }
        else
        {
            throw Exception("Invalid character!");
        }
    }
    
    public static BigInteger RadixConvert(int arr[], int len, int radix) throws Exception
    {
        if(len <= 0)
        {
            throw new Exception("len <= 0");
        }
        BigInteger a = BigInteger.valueOf(0);
        BigInteger posValue = BigInteger.valueOf(1);
        for(int i = len-1; i >= 0; --i)
        {
            a = a.add(posValue.multiply(BigInteger.valueOf(arr[i])));
            posValue = posValue.multiply(BigInteger.valueOf(radix));
        }
        return a;
    }

    private static Exception Exception(String invalid_character) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
}
