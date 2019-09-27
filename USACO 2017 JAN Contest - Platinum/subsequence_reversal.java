import java.util.Arrays;
import java.util.Scanner;

public class subrev {
    public static void main (String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        a = new int[n];
        for (int i = 0; i < n; i++) a[i] = in.nextInt();
        dp = new int[n][n][51][51];
        for (int[][][] x : dp) for (int[][] y : x) for (int[] z : y) Arrays.fill(z, -1);
        System.out.println(solve(0,n-1,0,50));
    }

    public static int[] a;
    public static int[][][][] dp;
    public static int solve(int i, int j, int k, int m) {
        if (dp[i][j][k][m] != -1) return dp[i][j][k][m];
        if (k > m) return -(1 << 29); // impossible case
        if (i > j) return 0;
        if (i == j) {
            if (a[i] >= k && a[i] <= m) return 1;
            else return 0;
        }
        // max value from interval [i,j] given we've taken k from prefix and m from suffix
        int res = 0;
        // case 1: swap i and j
        // case 1a: don't include a[i] or a[j]
        res = Math.max(res, solve(i+1,j-1,k,m));
        // case 1b: include a[j]
        if (a[j] >= k)
            res = Math.max(res, solve(i+1,j-1,a[j],m)+1);
        // case 1c: include a[i]
        if (a[i] <= m)
            res = Math.max(res, solve(i+1,j-1,k,a[i])+1);
        // case 1d: include both
        if (k <= a[j] && a[j] <= a[i] && a[i] <= m) {
            res = Math.max(res, solve(i+1,j-1,a[j],a[i])+2);
        }

        // case 2: don't swap, move i forward
        // case 2a: don't include a[i]
        res = Math.max(res, solve(i+1,j,k,m));
        // case 2b: include a[i]
        if (a[i] >= k)
            res = Math.max(res, solve(i+1,j,a[i],m)+1);

        // case 3: don't swap, move j backward
        // case 3a: don't include a[j]
        res = Math.max(res, solve(i,j-1,k,m));
        // case 3b: include a[j]
        if (a[j] <= m)
            res = Math.max(res, solve(i,j-1,k,a[j])+1);

        return dp[i][j][k][m] = res;
    }
}