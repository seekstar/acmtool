//package jiaozuo_online_2018_J;
import java.util.*;
import java.math.*;
public class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int T = in.nextInt();
		while (T-- != 0) {
			BigInteger n = in.nextBigInteger();
			boolean is1 = IsSquare(n);
			n = n.multiply(n.subtract(BigInteger.ONE)).shiftRight(1);
			boolean is2 = IsSquare(n);
			if (is1 && is2) {
				System.out.println("Arena of Valor");
			} else if (is1 && !is2) {
				System.out.println("Hearth Stone");
			} else if (!is1 && is2) {
				System.out.println("Clash Royale");
			} else {
				System.out.println("League of Legends");
			}
		}
		in.close();
	}
	public static boolean IsSquare(BigInteger x) {
		BigInteger sqr = sqrt(x);
		return sqr.multiply(sqr).equals(x);
	}
	public static BigInteger sqrt(BigInteger x) {
		BigInteger l = BigInteger.ZERO;
		BigInteger r = x;
		while (l.compareTo(r) <= 0) {
			BigInteger mid = l.add(r).shiftRight(1);
			if (mid.multiply(mid).compareTo(x) <= 0) {
				l = mid.add(BigInteger.ONE);
			} else {
				r = mid.subtract(BigInteger.ONE);
			}
		}
		return r;
	}
}

