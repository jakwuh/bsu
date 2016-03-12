'use strict';
const EPS = 1E-5, TOL = 0.5

let log = console.log, M = Math

let phi = (x) => (x - (f(x) / fd(x)))
let f = (x) => (M.exp(x) + M.sqrt(1 + M.exp(2 * x)) - 2)
let fd = (x) => (M.exp(x) + M.exp(2 * x) / M.sqrt(M.exp(2 * x) + 1))

let bisection = (r) => {
	while (r.b - r.a > TOL) {
	    let c = (r.b + r.a) / 2
	    if (M.abs(f(c)) < EPS) return { a: c, b: c }
	    f(c) * f(r.a) < 0 ? r.b = c : r.a = c
	}
	return r
}

let solve = (r) => {
	let x = (r.a + r.b) / 2, count = 1
    while (M.abs(x - (x = phi(x))) > EPS && ++count){}
    log(`The solution is ${x}+-${EPS} was found with ${count} iterations`)
}

solve(bisection({ a: -1, b: 1 }))