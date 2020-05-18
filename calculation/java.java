BigInteger x = in.nextBigInteger(), y = in.nextBigInteger();
BigInteger ans[] = x.divideAndRemainder(y);
System.out.printf("quotient: %d\nremainder: %d\n", ans[0], ans[1]);
