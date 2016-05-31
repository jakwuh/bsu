const {sin, cos, pow} = Math;
const {log} = console;
const {norm, subtract, multiply, inv, transpose} = require('mathjs');

const EPS = pow(10, -5);
const x0 = -1, y0 = -2;

const f = ([x, y]) => [2 * x * x - x * y - y * y + 2 * x - 2 * y + 6, y * sin(y) - x - 1];
const J = ([x, y]) => transpose([[4 * x - y + 2, -x - 2 * y - 2], [-1, sin(y) + y * cos(y)]]);
const phiS = (x) => subtract(x, multiply(f(x), inv(J([x0, y0]))));
const phiN = (x) => subtract(x, multiply(f(x), inv(J(x))));
const r = (a, b) => norm(subtract(a, b), 2);

const solve = (next, name) => {
	let x = [x0, y0], count = 0;
	while (r(x, x = next(x)) > EPS && ++count);
	log(`${name}: the solution was found with ${count} iterations, error is ${r(f(x), 0)}:`);
	console.log(x);
}

solve(phiS, 'Simple iterations');
solve(phiN, 'Newton');