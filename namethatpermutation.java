import java.math.BigInteger;
import java.util.Scanner;
import java.util.ArrayList;

public class namethatpermutation {  
  static BigInteger fact(int n) {
    BigInteger res = BigInteger.valueOf(n--);
    for(; n > 0; --n) {
      res = res.multiply(BigInteger.valueOf(n));
    }
    return res;
  }
  
  static ArrayList<Integer> numbers = new ArrayList<Integer>();
  
  static String thing(int n, BigInteger k) {
    if(n == 0) {
      return "";
    }
    
    BigInteger step = fact(n).divide(BigInteger.valueOf(n));
    BigInteger max = step;
    
    int i = 0;
    for(; i < n; ++i) {
      if(k.compareTo(max) == -1) {
        break;
      }
      max = max.add(step);
    }
    int number = numbers.remove(i);
    return number + " " + thing(n - 1, k.subtract(max.subtract(step)));
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while(s.hasNextInt()) {
      numbers.clear();
      int n = s.nextInt();
      BigInteger k = s.nextBigInteger();
      for(int i = 1; i <= n; ++i) {
        numbers.add(i);
      }
      System.out.println(thing(n, k));
    }
    s.close();
  }
}
