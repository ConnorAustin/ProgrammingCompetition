import java.util.Scanner;
import java.util.Arrays;
import java.util.ArrayList;

public class workstations {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int r_len = sc.nextInt();
        int activity = sc.nextInt();
        
        int[] arrives = new int[r_len];
        int[] leaves = new int[r_len];
        
        for(int r = 0; r < r_len; ++r) {
            int arrive = sc.nextInt();
            arrives[r] = arrive;
            
            int stays = sc.nextInt();
            leaves[r] = arrive + stays;
        }
        
        Arrays.sort(arrives);
        Arrays.sort(leaves);
        int result = 0;
        
        for(int r = 0; r < r_len; ++r) {
            int ar = arrives[r];
            
            for(int i = 0; i < r_len; ++i) {
                if(leaves[i] == -1) {
                    continue;
                }
                
                if(leaves[i] <= ar && leaves[i] + activity >= ar) {
                    ++result;
                    leaves[i] = -1;
                    break;
                }
            }
        }
        System.out.println(result);
        sc.close();
    }
}