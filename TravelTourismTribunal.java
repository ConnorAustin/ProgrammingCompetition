import java.util.Scanner;

public class TravelTourismTribunal {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while(sc.hasNext()) {
			int n = sc.nextInt();
			sc.nextLine();
			int[][] array = new int[n-1][n-1];
			for(int i = 0; i < n-1; i++) {
				for(int j = 0; j < n-1; j++) {
					if(i == j) array[i][j] = 0;
					else array[i][j] = -1;
				}
			}
			for(int i = 0; i < n-1; i++) {
				String line = sc.nextLine();
				String[] a = line.split(" ");
				for(int j = i; j < a.length; j++) {
					array[i][j] = Integer.parseInt(a[j]);
				}
			}
			for(int k = 0; k < n-1; k++) {
				for(int i = 0; i < n-1; i++) {
					for(int j = 0; j < n-1; j++) {
						if(array[i][j] == -1 || array[i][j] > array[i][k] + array[k][j])
							array[i][j] = array[i][k] + array[k][j];
					}
				}
			}
			for(int i = 0; i < n-1; i++) {
				for(int j = 0; j < n-1; j++) {
					System.out.print(array[i][j] + " ");
				}
				System.out.println();
			}
			System.out.println("The maximal shortest path takes " + " minutes.");
		}
		sc.close();
	}
}
