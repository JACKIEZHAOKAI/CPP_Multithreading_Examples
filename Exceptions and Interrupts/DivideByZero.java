public class DivideByZero {
    public static void main (String args[]) {
    try {
        int x = 0;
        System.out.println (1/x);
    } catch (ArithmeticException e) {
        System.out.print (e.getMessage());
        System.out.println (": zoinks! divide by zero");
    }
    }
}