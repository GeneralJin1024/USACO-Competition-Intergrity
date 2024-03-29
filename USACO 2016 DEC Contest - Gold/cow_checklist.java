import java.io.*;
import java.util.*;
public class checklist {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("checklist.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("checklist.out")));
		StringTokenizer st = new StringTokenizer(br.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		State[] holstein = new State[n];
		State[] guernsey = new State[m];
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(br.readLine());
			holstein[i] = new State(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
		}
		for(int i = 0; i < m; i++) {
			st = new StringTokenizer(br.readLine());
			guernsey[i] = new State(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
		}
		long[][][] dp = new long[n+1][m+1][2];
		for(int i = 0; i < dp.length; i++) {
			for(int j = 0; j < dp[i].length; j++) {
				Arrays.fill(dp[i][j], 1L << 60);
			}
		}
		dp[1][0][0] = 0;
		for(int i = 0; i < dp.length; i++) {
			for(int j = 0; j < dp[i].length; j++) {
				for(int k = 0; k < 2; k++) {
					if(k == 0 && i == 0) continue;
					if(k == 1 && j == 0) continue;
					State source;
					if(k == 0) source = holstein[i-1];
					else source = guernsey[j-1];
					if(i < n) {
						dp[i+1][j][0] = Math.min(dp[i+1][j][0], dp[i][j][k] + source.dist(holstein[i]));
					}
					if(j < m) {
						dp[i][j+1][1] = Math.min(dp[i][j+1][1], dp[i][j][k] + source.dist(guernsey[j]));
					}
				}
			}
		}
		pw.println(dp[n][m][0]);
		pw.close();
	}

	static class State {
		public int x, y;
		public State(int a, int b) {
			x=a;
			y=b;
		}
		public int dist(State s) {
			return (x-s.x)*(x-s.x) + (y-s.y)*(y-s.y);
		}
	}
	
}