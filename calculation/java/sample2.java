import java.util.*;
import java.math.*;

public class Main {
	//Vector<Vector<int> > sons;
	static int sons[][];
	static boolean vis[][];
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		
		int n = in.nextInt();
		vis = new boolean[n+1][2];
		sons = new int[n+1][];
		g = new int[n+1][2];
		f = new BigInteger[n+1][2];
		for (int i = 1; i <= n; ++i) {
			int u = in.nextInt();
			int m = in.nextInt();
			sons[u] = new int[m];
			while (m != 0) {
				sons[u][--m] = in.nextInt();
			}
		}
		
		boolean isSon[] = new boolean[n+1];
		for (int i = 1; i <= n; ++i) {
			for (int v : sons[i]) {
				isSon[v] = true;
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (!isSon[i]) {
				System.out.println(Math.max(dpg(i, 0), dpg(i, 1)));
				for (int j = 1; j <= n; ++j) {
					vis[j][0] = vis[j][1] = false;
				}
				if (g[i][0] == g[i][1]) {
					System.out.println(dpf(i, 0).add(dpf(i, 1)));
				} else if (g[i][0] < g[i][1]) {
					System.out.println(dpf(i, 1));
				} else {
					System.out.println(dpf(i, 0));
				}
			}
		}
		in.close();
	}
	
	static int g[][];
	public static int dpg(int i, int exist) {
		if (vis[i][exist]) {
			return g[i][exist];
		}
		int ans;
		if (exist != 0) {
			ans = 0;
			for (int k : sons[i]) {
				int now = dpg(k, 0) + 1;
				for (int j : sons[i]) {
					if (j == k) continue;
					now += Math.max(dpg(j, 0), dpg(j, 1));
				}
				ans = Math.max(ans, now);
			}
		} else {
			ans = 0;
			for (int j : sons[i]) {
				ans += Math.max(dpg(j, 0), dpg(j, 1));
			}
		}
		vis[i][exist] = true;
		g[i][exist] = ans;
		return ans;
	}
	
	static BigInteger f[][];
	public static BigInteger dpf(int i, int exist) {
		if (vis[i][exist]) {
	        return f[i][exist];
	    }
	    BigInteger ans;
	    if (exist != 0) {
	        ans = BigInteger.ZERO;
	        for (int k : sons[i]) {
	            int now = g[k][0] + 1;
	            for (int j : sons[i]) {
	                if (j == k) continue;
	                now += Math.max(g[j][0], g[j][1]);
	            }
	            if (now == g[i][1]) {
	            	BigInteger tmp = BigInteger.ONE;
	                tmp = tmp.multiply(dpf(k, 0));
	                if (tmp == BigInteger.ZERO) continue;
	                for (int j : sons[i]) {
	                    if (j == k) continue;
	                    if (g[j][0] == g[j][1]) {
	                        tmp = tmp.multiply(dpf(j, 0).add(dpf(j, 1)));
	                    } else if (g[j][0] < g[j][1]) {
	                        tmp = tmp.multiply(dpf(j, 1));
	                    } else {
	                    	tmp = tmp.multiply(dpf(j, 0));
	                    }
	                }
	                ans = ans.add(tmp);
	            }
	        }
	    } else {
	        ans = BigInteger.ONE;
	        for (int j : sons[i]) {
	        	if (g[j][0] == g[j][1]) {
	        		ans = ans.multiply(dpf(j, 0).add(dpf(j, 1)));
                } else if (g[j][0] < g[j][1]) {
                	ans = ans.multiply(dpf(j, 1));
                } else {
                	ans = ans.multiply(dpf(j, 0));
                }
	        }
	    }
	    vis[i][exist] = true;
	    f[i][exist] = ans;
	    return ans;
	}
}

