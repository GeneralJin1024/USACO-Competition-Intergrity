import java.io.*;
import java.util.*;
public class nocross {
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new FileReader("nocross.in"));
		PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("nocross.out")));
		int n = Integer.parseInt(br.readLine());
		int[] l = new int[n];
		for(int i = 0; i < n; i++) {
			l[i] = Integer.parseInt(br.readLine())-1;
		}
		int[] locOf = new int[n];
		for(int i = 0; i < n; i++) {
			locOf[Integer.parseInt(br.readLine()) - 1] = i;
		}
		RangeTree dp = new RangeTree(n+1);
		for(int i = 0; i < n; i++) {
			ArrayList<Integer> indices = new ArrayList<Integer>();
			for(int a = Math.max(0, l[i] - 4); a < Math.min(n, l[i] + 5); a++) {
				indices.add(locOf[a]);
			}
			Collections.sort(indices);
			for(int a = indices.size()-1; a >= 0; a--) {
				dp.update(indices.get(a)+1, dp.query(0, indices.get(a)) + 1);
			}
		}
		pw.println(dp.query(0, n));
		pw.close();
	}
	
	static class RangeTree {
		int[] leaf;
		int size;
		public RangeTree(int n) {
			leaf = new int[4*n];
			size = n;
		}
		public void update(int index, int val) {
			update(1, 0, size-1, index, val);
		}
		private void update(int index, int l, int r, int i, int v) {
			if(l == r) {
				leaf[index] = v;
			}
			else {
				int m = (l+r)/2;
				if(i <= m) {
					update(2*index, l, m, i, v);
				}
				else {
					update(2*index+1, m+1, r, i, v);
				}
				leaf[index] = Math.max(leaf[2*index], leaf[2*index+1]);
			}
		}
		public int query(int l, int r) {
			return query(1, 0, size-1, l, r);
		}
		public int query(int index, int l, int r, int lhs, int rhs) {
			if(l >= lhs && r <= rhs) {
				return leaf[index];
			}
			int ret = 0;
			int m = (l+r)/2;
			if(m >= lhs) {
				ret = Math.max(ret, query(2*index, l, m, lhs, rhs));
			}
			if(m+1 <= rhs) {
				ret = Math.max(ret, query(2*index+1, m+1, r, lhs, rhs));
			}
			return ret;
		}
	}
	
}