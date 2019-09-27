import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.io.BufferedReader;
import java.io.InputStream;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        OutputWriter out = new OutputWriter(outputStream);
        friendcross solver = new friendcross();
        solver.solve(1, in, out);
        out.close();
    }

    static class friendcross {
        public int[] arr;
        public int[] brr;
        public static int[] seq;

        public void solve(int testNumber, InputReader in, OutputWriter out) {
            int n = in.nextInt(), k = in.nextInt();
            arr = in.readIntArray(n);
            brr = in.readIntArray(n);
            int[] ra = new int[n + 1];
            int[] rb = new int[n + 1];
            for (int i = 0; i < n; i++) {
                ra[arr[i]] = i + 1;
                rb[brr[i]] = i + 1;
            }

            seq = new int[n + 1];
            for (int i = 1; i <= n; i++) {
                seq[ra[i]] = rb[i];
            }
            friendcross.SegmentTree root = new friendcross.SegmentTree(1, n);
            ArrayList<friendcross.Event>[] events = new ArrayList[n + 1];
            for (int i = 0; i <= n; i++) events[i] = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                int up = Math.min(n, i + k);
                int down = Math.max(0, i - k - 1);
                events[up].add(new friendcross.Event(i, +1));
                events[down].add(new friendcross.Event(i, -1));
            }
            long tinv = 0;
            BIT x = new BIT(n);
            for (int i = 1; i <= n; i++) {
                x.update(seq[i], +1);
                tinv += i - x.query(seq[i]);
            }
            long res = 0;
            for (int cow = 1; cow <= n; cow++) {
                root.update(ra[cow], +1);
                for (friendcross.Event e : events[cow])
                    res += e.sign * root.query(1, ra[e.cow], rb[e.cow]);
            }
            out.println(tinv - res);
        }

        static class Event {
            public int cow;
            public int sign;

            public Event(int cow, int sign) {
                this.cow = cow;
                this.sign = sign;
            }

        }

        static class SegmentTree {
            public int[] arr;
            public int[] pl;
            public int[] pr;
            public BIT bit;
            public int start;
            public int end;
            public friendcross.SegmentTree lchild;
            public friendcross.SegmentTree rchild;

            public SegmentTree(int start, int end) {
                this.start = start;
                this.end = end;
                arr = new int[end - start + 2];
                if (start == end) {
                    arr[1] = seq[start];
                } else {
                    int mid = (start + end) >> 1;
                    lchild = new friendcross.SegmentTree(start, mid);
                    rchild = new friendcross.SegmentTree(mid + 1, end);
                    pl = new int[lchild.arr.length];
                    pr = new int[rchild.arr.length];
                    int lidx = 1, ridx = 1;

                    int idx = 1;
                    int[] larr = lchild.arr, rarr = rchild.arr;
                    while (lidx < larr.length && ridx < rarr.length) {
                        if (larr[lidx] < rarr[ridx]) {
                            pl[lidx] = idx;
                            arr[idx++] = larr[lidx++];
                        } else {
                            pr[ridx] = idx;
                            arr[idx++] = rarr[ridx++];
                        }
                    }
                    while (lidx < larr.length) {
                        pl[lidx] = idx;
                        arr[idx++] = larr[lidx++];
                    }
                    while (ridx < rarr.length) {
                        pr[ridx] = idx;
                        arr[idx++] = rarr[ridx++];
                    }
                }
                bit = new BIT(end - start + 2);
            }

            public int query(int s, int e, int k) {
                if (start == s && end == e) {
                    if (k < arr[1]) return bit.count;
                    int lo = 1, hi = arr.length - 1;
                    while (lo < hi) {
                        int mid = (lo + hi + 1) / 2;
                        if (arr[mid] > k) hi = mid - 1;
                        else lo = mid;
                    }
                    return bit.count - bit.query(lo);
                }
                int mid = (start + end) >> 1;
                if (mid >= e) return lchild.query(s, e, k);
                else if (mid < s) return rchild.query(s, e, k);
                else return lchild.query(s, mid, k) + rchild.query(mid + 1, e, k);
            }

            public int update(int p, int val) {
                if (start == p && end == p) {
                    bit.update(1, +1);
                    return 1;
                }
                int mid = (start + end) >> 1;
                int apos = -1;
                if (mid >= p) apos = pl[lchild.update(p, val)];
                else apos = pr[rchild.update(p, val)];
                bit.update(apos, +1);
                return apos;
            }

        }

    }

    static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;

        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }

        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }

        public int[] readIntArray(int tokens) {
            int[] ret = new int[tokens];
            for (int i = 0; i < tokens; i++) {
                ret[i] = nextInt();
            }
            return ret;
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

    }

    static class BIT {
        private int[] tree;
        private int N;
        public int count;

        public BIT(int N) {
            this.N = N;
            this.tree = new int[N + 1];
            this.count = 0;
        }

        public int query(int K) {
            int sum = 0;
            for (int i = K; i > 0; i -= (i & -i))
                sum += tree[i];
            return sum;
        }

        public void update(int K, int val) {
            this.count += val;
            for (int i = K; i <= N; i += (i & -i))
                tree[i] += val;
        }

    }

    static class OutputWriter {
        private final PrintWriter writer;

        public OutputWriter(OutputStream outputStream) {
            writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
        }

        public OutputWriter(Writer writer) {
            this.writer = new PrintWriter(writer);
        }

        public void close() {
            writer.close();
        }

        public void println(long i) {
            writer.println(i);
        }

    }
}