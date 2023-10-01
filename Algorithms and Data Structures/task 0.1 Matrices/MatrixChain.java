public class MatrixChain {
   public static int multiplyOrder(int[] p) {
       int n = p.length - 1;
       int[][] dp = new int[n][n];
       
       for (int i = 0; i < n; ++i) {
           dp[i][i] = 0;
       }
       
       for (int l = 1; l < n; l++) {
           for (int i = 0; i < n - l; i++) {
               int j = i + l;
               dp[i][j] = Integer.MAX_VALUE;
               for (int k = i; k < j; k++) {
                   dp[i][j] = Math.min(dp[i][j], dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1]);
               }
           }
       }
       return dp[0][n - 1]; 
   }
   
   public static void main(String[] args) {
       int[] test = { 20, 5, 35, 4, 25 };
       System.out.println(MatrixChain.multiplyOrder(test));
   }
}