import java.math.BigInteger;
import java.util.Scanner;

public class NNRsa {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while(true) {
            BigInteger m = sc.nextBigInteger();
            BigInteger e = sc.nextBigInteger();
            
            if(m.equals(BigInteger.ZERO) && e.equals(BigInteger.ZERO)) {
                break;
            }
            
            if(e.compareTo(BigInteger.valueOf(Integer.MAX_VALUE) > 0) {
                
            }
        }
        sc.close();
    }
}
