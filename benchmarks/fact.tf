

fact_inner <- if(eq(#0,0), #1, fact_inner(sub(#0,1), mul(#0,#1)))
fact <- fact_inner(#0, 1)

fact(10)