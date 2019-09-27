import java.io.*;
import java.util.*;
public class promote {
	
	static LinkedList<Integer>[] children;
	
	static int[] size;
	static int[] start;
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("promote.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("promote.out")));
		int n = Integer.parseInt(br.readLine());
		children = new LinkedList[n];
		for(int i = 0; i < n; i++) {
			children[i] = new LinkedList<Integer>();
		}
		State[] l = new State[n];
		for(int i = 0; i < n; i++) {
			l[i] = new State(i, Integer.parseInt(br.readLine()));
		}
		Arrays.sort(l);
		for(int i = 1; i < n; i++) {
			children[Integer.parseInt(br.readLine()) - 1].add(i);
		}
		size = new int[n];
		start = new int[n];
		dfs(0);
		int[] ret = new int[n];
		BIT bit = new BIT(n);
		for(State out: l) {
			int rhs = start[out.index] + size[out.index] - 1;
			int lhs = start[out.index];
			ret[out.index] = bit.query(rhs) - bit.query(lhs);
			bit.increment(start[out.index]);
		}
		for(int out: ret) {
			pw.println(out);
		}
		pw.close();
	}

	static int numSeen = 0;
	public static void dfs(int index) {
		start[index] = numSeen++;
		size[index]++;
		for(int out: children[index]) {
			dfs(out);
			size[index] += size[out];
		}
	}
	
	static class State implements Comparable<State> {
		public int index, val;

		public State(int index, int val) {
			this.index = index;
			this.val = val;
		}

		public int compareTo(State s) {
			return s.val - val;
		}
		
	}
	
	static class BIT {
		int[] leaf;
		public BIT(int s) {
			leaf = new int[s+5];
		}
		public void increment(int x) {
			x+=2;
			while(x < leaf.length) {
				leaf[x]++;
				x += x & -x;
			}
		}
		public int query(int x) {
			int ret = 0;
			x+=2;
			while(x > 0) {
				ret += leaf[x];
				x -= x & -x;
			}
			return ret;
		}
	}
	
}