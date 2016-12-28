require('console.table')
const {eval, sum, subtract, factorial} = require('mathjs')
const {last, takeRight} = require('lodash')
const {sqrt, pow, abs} = Math

const array = n => [...Array(n).keys()]
const range = (a, b, n = 1) => array(n + 1).map(i => a + (b - a) / n * i)
const toFixed = n => v => Number(v.toPrecision(3)).toExponential()

const solution = x => eval(`(sqrt(25 - 4x^2) + 5) / (2x^2)`, {x})
const yd = [
    (x, y) => y,
    (x, y) => eval(`2 x y^3 / (1 - x^2 y^2)`, {x, y}),
    (x, y) => eval(`2 y^2 (-x^3 y^2 y' + x^2 y^3 + 3 x y' + y) / (1 - x^2 y^2)^2`, {x, y, "y'": yd[1](x, y)}),
    (x, y) => eval(`(4 y * (-x * (x^2 y^2 + 3) * yd ^2 - x * (x^2 y^2 + 3) * y^4 + (x^4 y^4 - 6 x^2 y^2 - 3) * y yd ) - 2 x y^2 (x^4 y^4 - 4 x^2 y^2 + 3) ydd )/(x^2 y^2 - 1)^3`, {x, y, "yd": yd[1](x, y), "ydd": yd[2](x, y)})
]

const f = yd[1]
const EPS = 1E-8
const v = range(2, 2.45, 9)
const y0 = 1
const y = v.map(solution)
const h = v[1] - v[0]

const taylor = yd => (x, y) => sum(yd.map((f, i) => f(x, y) * pow(h, i) / factorial(i)))

const newton = (xn, y, yn = taylor(yd.slice(0, 2))(xn - h, y)) => {
    const fy = yn => eval(`(6 x y^2 - 10 x^3 y^4) / (1 - x^2 y^2)^2`, {x: xn, y: yn})
    const phi = yn => ((y + h * f(xn, yn) - h * yn * fy(yn)) / (1 - h * fy(yn)))
    while (abs(yn - (yn = phi(yn))) > EPS);
    return yn
}

const next_series = ({xn, yn}) => taylor(yd)(xn, yn);
const next_exp_euler = ({xn, yn}) => taylor(yd.slice(0, 2))(xn, yn);
const next_imp_euler = ({xn, yn}) => newton(xn + h, yn)
const next_runge_kutta = ({xn, yn}) => yn + h * f(xn - h / 2, yn + h / 2 * f(xn - h, yn))
const next_pred_corr = ({xn, yn}) => {
    const yn1_4 = yn + h / 4 * f(xn, yn)
    const yn1_2 = yn + h / 2 * f(xn + h / 4, yn1_4)
    const yn1 = yn + h * f(xn + h / 2, yn1_2) 
    return yn + h / 6 * (f(xn, yn) + 4 * f(xn + h / 2, yn1_2) + f(xn + h, yn1))
}

const run = next => v.slice(1).reduce((yv, x) => {
    const xn = x - h
    const yn = last(yv)
    return [...yv, next({xn, yn})]
}, [y0])

const y_series = run(next_series)
const y_exp_euler = run(next_exp_euler)
const y_imp_euler = run(next_imp_euler)
const y_runge_kutta = run(next_runge_kutta)
const y_pred_corr = run(next_pred_corr)

const y_ext_adams = v.slice(3).reduce((yv, x) => {
    const ys = takeRight(yv, 3), xs = [x - 3 * h, x - 2 * h, x - h]
    return [...yv, ys[2] + h / 12 * (23 * f(xs[2], ys[2]) - 16 * f(xs[1], ys[1]) + 5 * f(xs[0], ys[0]))]
}, y_pred_corr.slice(0, 3))

const toAnswer = obj => {
    const key = Object.keys(obj)[0]
    return [[key], subtract(obj[key], y).map(toFixed(8))]
}

console.table([
    ['x'], v.map(v => v.toFixed(8)),
    ['y'], y.map(v => v.toFixed(8)),
    ...toAnswer({y_series}), // 4 >> 3
    ...toAnswer({y_exp_euler}), // 2 >> 1
    ...toAnswer({y_imp_euler}), // 2 >> 1
    ...toAnswer({y_runge_kutta}), // 4 >> 3
    ...toAnswer({y_pred_corr}), // 4 >> 3
    ...toAnswer({y_ext_adams}) // 5 >> 4
])
