require('console.table')
const {eval, sum, subtract, factorial} = require('mathjs')
const {last, takeRight} = require('lodash')
const {sqrt, pow, abs, max} = Math

const array = n => [...Array(n).keys()]
const range = (a, b, n = 1) => array(n + 1).map(i => a + (b - a) / n * i)
const toFixed = n => v => Number(v.toPrecision(3)).toExponential()

let zd = [], yd = []

const solutiony = x => {
    if (x < 0.05) return 0
    else if (x < 0.15) return 0.00475249
    else if (x < 0.25) return 0.0181113
    else if (x < 0.35) return 0.0388025
    else if (x < 0.45) return 0.0654698
    else if (x < 0.55) return 0.0965414
    else if (x < 0.65) return 0.130223
    else if (x < 0.75) return 0.164614
    else if (x < 0.85) return 0.197897
    else if (x < 0.95) return 0.228545
    else if (x < 1.05) return 0.255464
}
const solutionz = x => {
    if (x < 0.05) return -0.4122
    else if (x < 0.15) return -0.412009
    else if (x < 0.25) return -0.376578
    else if (x < 0.35) return -0.306296
    else if (x < 0.45) return -0.204098
    else if (x < 0.55) return 0.0754778
    else if (x < 0.65) return 0.0719367
    else if (x < 0.75) return 0.229236
    else if (x < 0.85) return 0.387364
    else if (x < 0.95) return 0.538275
    else if (x < 1.05) return 0.675794
}

yd = [
    (x, y, z) => y,
    (x, y, z) => eval(`-y z + sin(x) / (1 + x)`, {x, y, z}),
    (x, y, z) => eval(`-yd z - y zd + cos(x) / (1 + x) - sin(x) / (1 + x)^2`, {x, y, z, yd: yd[1](x, y, z), zd: zd[1](x, y, z)}),
    (x, y, z) => eval(`-ydd z - 2 yd zd - y zdd + -sin(x) / (1 + x) - 2 cos(x) / (1 + x)^2 + 2 sin(x) / (1 + x)^3`, {x, y, z, yd: yd[1](x, y, z), ydd: yd[2](x, y, z), zd: zd[1](x, y, z), zdd: zd[2](x, y, z)})
]

zd = [
    (x, y, z) => z,
    (x, y, z) => eval(`-z^2 + 3.5 x / (1 + x^2)`, {x, z}),
    (x, y, z) => eval(`-2 z zd + 3.5 / (1 + x^2) - 7x^2 / (1 + x^2)^2`, {x, z, zd: zd[1](x, y, z)}),
    (x, y, z) => eval(`-2 z zdd - 2 zd ^ 2 - 7x / (1 + x^2)^2 - 14x / (1 + x^2)^2 + 28 x^3 / (1 + x^2)^3`, {x, z, zd: zd[1](x, y, z), zdd: zd[2](x, y, z)})
]

const f1 = yd[1]
const f2 = zd[1]
const EPS = 1E-8
const v = range(0, 1, 10)
const y0 = 0
const z0 = -0.4122
const h = v[1] - v[0]

const y = v.map(solutiony)
const z = v.map(solutionz)

const taylor = fd => (x, y, z) => sum(fd.map((f, i) => f(x, y, z) * pow(h, i) / factorial(i)))

const newton = (xn1, yn, zn) => {
    let yn1 = taylor(yd.slice(0, 2))(xn1 - h, yn, zn)
    let zn1 = taylor(zd.slice(0, 2))(xn1 - h, yn, zn)
    const f1y = (y, z) => -z
    const f2z = (y, z) => -2 * z

    const phi = (f, fd) => (yn1, zn1) => ((yn + h * f(xn1, yn1, zn1) - h * yn1 * fd(yn1, zn1)) / (1 - h * fd(yn1, zn1)))
    const phi1 = phi(f1, f1y)
    const phi2 = phi(f2, f2z)
    let err = 10
    while (err > EPS) {
        let prev_yn1 = yn1, prev_zn1 = zn1
        yn1 = phi1(yn1, zn1)
        zn1 = phi2(yn1, zn1)
        err = max(abs(yn1 - prev_yn1), abs(zn1 - prev_zn1))
    }
    return [yn1, zn1]
}

const next_series = ({xn, yn, zn}) => [taylor(yd)(xn, yn, zn), taylor(zd)(xn, yn, zn)];
const next_exp_euler = ({xn, yn, zn}) => [
    taylor(yd.slice(0, 2))(xn, yn, zn), 
    taylor(zd.slice(0, 2))(xn, yn, zn)
];
const next_imp_euler = ({xn, yn, zn}) => newton(xn + h, yn, zn)
const next_runge_kutta = ({xn, yn, zn}) => {
    yn1 = h * f1(xn, yn, zn)
    zn1 = h * f2(xn, yn, zn)
    yn2 = h * f1(xn + 2 / 3 * h, yn + 2 / 3 * yn1, zn + 2 / 3 * zn1)
    zn2 = h * f2(xn + 2 / 3 * h, yn + 2 / 3 * yn1, zn + 2 / 3 * zn1)
    return [
        yn + 1 / 4 * (yn1 + 3 * yn2),
        zn + 1 / 4 * (zn1 + 3 * zn2)
    ]
}
const next_pred_corr = ({xn, yn, zn}) => {
    const yn1_4 = yn + h / 4 * f1(xn, yn, zn)
    const zn1_4 = zn + h / 4 * f2(xn, yn, zn)
    const yn1_2 = yn + h / 2 * f1(xn + h / 4, yn1_4, zn1_4)
    const zn1_2 = zn + h / 2 * f2(xn + h / 4, yn1_4, zn1_4)
    const yn1 = yn + h * f1(xn + h / 2, yn1_2, zn1_2) 
    const zn1 = zn + h * f2(xn + h / 2, yn1_2, zn1_2) 
    return [
        yn + h / 6 * (f1(xn, yn, zn) + 4 * f1(xn + h / 2, yn1_2, zn1_2) + f1(xn + h, yn1, zn1)),
        zn + h / 6 * (f2(xn, yn, zn) + 4 * f2(xn + h / 2, yn1_2, zn1_2) + f2(xn + h, yn1, zn1)),
    ]
}

const run = next => v.slice(1).reduce((yv, x) => {
    const xn = x - h
    const [yn, zn] = last(yv)
    return [...yv, next({xn, yn, zn})]
}, [[y0, z0]])

const y_series = run(next_series)
const y_exp_euler = run(next_exp_euler)
const y_imp_euler = run(next_imp_euler)
const y_runge_kutta = run(next_runge_kutta)
const y_pred_corr = run(next_pred_corr)

const y_int_adams = v.slice(2).reduce((yv, x) => {
    const yzs = takeRight(yv, 2), xs = [x - 2 * h, x - h, x]
    let yn1 = taylor(yd.slice(0, 2))(xs[1], yzs[1][0], yzs[1][1])
    let zn1 = taylor(zd.slice(0, 2))(xs[1], yzs[1][0], yzs[1][1])

    let err = 10
    while (err > EPS) {
        let prev_yn1 = yn1, prev_zn1 = zn1
        yn1 = yzs[1][0] + h / 12 * (5 * f1(xs[2], yn1, zn1) + 8 * f1(xs[1], yzs[1][0], yzs[1][1]) - f1(xs[0], yzs[0][0], yzs[0][1]))
        zn1 = yzs[1][1] + h / 12 * (5 * f2(xs[2], yn1, zn1) + 8 * f2(xs[1], yzs[1][0], yzs[1][1]) - f2(xs[0], yzs[0][0], yzs[0][1]))
        err = max(abs(yn1 - prev_yn1), abs(zn1 - prev_zn1))
    }
    return [...yv, [yn1, zn1]]
}, y_pred_corr.slice(0, 2))

const toAnswer = obj => {
    const key = Object.keys(obj)[0]
    return [
        [key], 
        subtract(obj[key].map(v => v[0]), y).map(toFixed(8)),
        subtract(obj[key].map(v => v[1]), z).map(toFixed(8))
    ]
}

console.table([
    ['x'], v.map(v => v.toFixed(8)),
    ['y'], y.map(v => v.toFixed(8)),
    ['z'], z.map(v => v.toFixed(8)),
    ...toAnswer({y_series}),
    ...toAnswer({y_exp_euler}),
    ...toAnswer({y_imp_euler}),
    ...toAnswer({y_runge_kutta}),
    ...toAnswer({y_pred_corr}),
    ...toAnswer({y_int_adams})
])
