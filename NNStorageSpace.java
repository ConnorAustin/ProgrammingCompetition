import java.util.Scanner;
import java.util.ArrayList;

class Item {
    public int value, weight;
}

public class NNStorageSpace {
    public static int best_value(ArrayList<Item> items, int index, int cur_weight, int cur_value, int limit) {
        if(index == items.size() || cur_weight > limit) {
            return cur_value;
        }
        
        int new_weight = cur_weight + items.get(index).weight;
        if(new_weight > limit) {
            return best_value(items, index + 1, cur_weight, cur_value, limit);
        }

        int new_value = cur_value + items.get(index).value;
        return Math.max(best_value(items, index + 1, new_weight, new_value, limit),
                        best_value(items, index + 1, cur_weight, cur_value, limit));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        scanner.useDelimiter("\\s*,\\s*");
        while(scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] split = line.split(" ");
            
            int limit = Integer.parseInt(split[0]);
            String[] items = split[1].split(",");
            
            ArrayList<Item> item_list = new ArrayList<Item>();
            
            for(int i = 0; i < items.length; ++i) {
                String[] details = items[i].split(":");
                
                Item item = new Item();
                item.weight = Integer.parseInt(details[0]);
                item.value = Integer.parseInt(details[1]);
                
                item_list.add(item);
            }
            System.out.println(best_value(item_list, 0, 0, 0, limit));
        }
        scanner.close();
    }
}