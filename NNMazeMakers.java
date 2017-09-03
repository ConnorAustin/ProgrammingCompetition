import java.util.Scanner;

class Cell {
    boolean l, b, r, t;
    boolean visited;
    int x, y;
    
    public Cell(int x, int y, boolean l, boolean b, boolean r, boolean t) {
        this.x = x;
        this.y = y;
        
        this.l = l;
        this.b = b;
        this.r = r;
        this.t = t;
        visited = false;
    }
}

public class NNMazeMakers {
    static int width, height;
    static Cell[][] cells;
    static boolean multiple_paths = false;
    static boolean solvable = false;
    static final Cell dummy = new Cell(-1, -1, false, false, false, false);
    
    static Cell findEntrance() {
        // Top              
        for(int x = 0; x < width; ++x) {
            Cell c = cells[x][0];
            if(c.t) {
                return c;
            }
        }
        
        // Bottom             
        for(int x = 0; x < width; ++x) {
            Cell c = cells[x][height - 1];
            if(c.b) {
                return c;
            }
        }
        
        // Left             
        for(int y = 0; y < height; ++y) {
            Cell c = cells[0][y];
            if(c.l) {
                return c;
            }
        }
        
        // Right             
        for(int y = 0; y < height; ++y) {
            Cell c = cells[width - 1][y];
            if(c.r) {
                return c;
            }
        }
        
        return null;
    }
    
    static void start(Cell entrance) {
        if(entrance.x == 0) {
            entrance.l = false;
        }
        if(entrance.x == width - 1) {
            entrance.r = false;
        }
        
        if(entrance.y == 0) {
            entrance.t = false;
        } 
        if(entrance.y == height - 1) {
            entrance.b = false;
        }
        fill(entrance, dummy);
    }
    
    static boolean check(Cell n) {
        if(n != null && n.visited) {
            multiple_paths = true;
            return false;
        }
        return n != null;
    }
    
    static void check_exit(Cell cell) {
        if(solvable) {
            return;
        }
        
        if(cell.x == 0 && cell.l) {
            cell.l = false;
            solvable = true;
        }
        
        if(cell.x == width - 1 && cell.r) {
            cell.r = false;
            solvable = true;
        }
        
        if(cell.y == 0 && cell.t) {
            cell.t = false;
            solvable = true;
        }
        
        if(cell.y == height - 1 && cell.b) {
            cell.b = false;
            solvable = true;
        }
    }
    
    static void fill(Cell cell, Cell parent) {
        // T, L, B, R
        cell.visited = true;
        
        check_exit(cell);
        
        Cell t = cell.t ? cells[cell.x][cell.y - 1] : null;
        if(t == parent) {
            t = null;
        }
        
        Cell l = cell.l ? cells[cell.x - 1][cell.y] : null;
        if(l == parent) {
            l = null;
        }
        
        Cell b = cell.b ? cells[cell.x][cell.y + 1] : null;
        if(b == parent) {
            b = null;
        }
        
        Cell r = cell.r ? cells[cell.x + 1][cell.y] : null;
        if(r == parent) {
            r = null;
        }
        
        if(check(t)) {
            fill(t, cell);
        }
        
        if(check(l)) {
            fill(l, cell);
        }
        
        if(check(b)) {
            fill(b, cell);
        }
        
        if(check(r)) {
            fill(r, cell);
        }
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean first = true;
        while(true) {
            multiple_paths = false;
            solvable = false;
            
            String[] dim = sc.nextLine().split(" ");
            
            height = Integer.parseInt(dim[0]);
            width = Integer.parseInt(dim[1]);
            if(height == 0) {
                break;
            }
            
            cells = new Cell[width][height];
            
            for(int y = 0; y < height; ++y) {
                String line = sc.nextLine();
                
                for(int x = 0; x < width; ++x) {
                    int val = Integer.parseInt("" + line.charAt(x), 16);
                    
                    boolean left = (val & 1) == 0;
                    boolean bottom = (val & (1 << 1)) == 0;
                    boolean right = (val & (1 << 2)) == 0;
                    boolean top = (val & (1 << 3)) == 0;
                    
                    cells[x][y] = new Cell(x, y, left, bottom, right, top);
                }
            }
            
            // Entrance find
            Cell entrance = findEntrance();
            if(entrance == null) {
                System.out.println("NO SOLUTION");
                continue;
            }
            start(entrance);
            
            if(!solvable) {
                System.out.println("NO SOLUTION");
                continue;
            }
            
            boolean unreachable = false;
            for(int y = 0; y < height; ++y) {
                for(int x = 0; x < width; ++x) {
                    if(!cells[x][y].visited) {
                        unreachable = true;
                        continue;
                    }
                }
            }
            if(unreachable) {
                System.out.println("UNREACHABLE CELL");
                continue;
            }
            
            if(multiple_paths) {
                System.out.println("MULTIPLE PATHS");
                continue;
            }
            
            System.out.println("MAZE OK");
        }
        sc.close();
    }
}