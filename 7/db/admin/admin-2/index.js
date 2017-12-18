const mysql      = require('mysql');
const fs = require('fs');
const Koa = require('koa');
const Router = require('koa-router');
const proxy = require('koa-proxy');

const connection = mysql.createConnection({
  host     : 'localhost',
  user     : 'root',
  password : 'admin',
  database : 'mydb',
  multipleStatements: true
});

connection.connect();

makeQuery('SELECT 1 + 1 AS solution').then(console.log);

async function makeQuery(query) {
    console.log(query);
    return new Promise((resolve, reject) => {
        connection.query(query, function (error, results, fields) {
          if (error) reject(error);
          else resolve(results);
        });
    });
}

async function executeQuery(name) {
    let query = fs.readFileSync(`${__dirname}/sql/${name}.sql`).toString();
    return makeQuery(query);
}

const app = new Koa();
const router = new Router();

router.get('/drop-triggers', async (ctx, next) => {
    console.log('drop-triggers');
    let results = await executeQuery('drop-triggers');
    console.log(results);
    await next();

    ctx.body = ctx.body.replace('<!--result-->', JSON.stringify(results, null, 2));
});

router.get('/create-triggers', async (ctx, next) => {
    console.log('create-triggers');
    let results = await executeQuery('create-triggers');
    console.log(results);
    await next();

    ctx.body = ctx.body.replace('<!--result-->', JSON.stringify(results, null, 2));
});

router.get('/make-select', async (ctx, next) => {
    console.log('select');
    let query = ctx.query.query;
    let results = await makeQuery(query);
    console.log(results);
    await next();

    ctx.body = ctx.body.replace('<!--result-->', JSON.stringify(results, null, 2));
});

app
  .use(router.routes())
  .use(router.allowedMethods());

app.use(proxy({
  host:  'http://localhost:3000',
  match: /^\/(csslib|jslib|express|boot)/
}))

app.use(ctx => {
    ctx.type = 'html';
    ctx.body = fs.readFileSync(`${__dirname}/index.html`).toString();
});

app.listen(3001, () => {
    console.log('Server is listening on http://localhost:3001');
});
