docker-compose -f ./mysql-compose.yml up &
sleep 20s
admin/node_modules/.bin/admin ./admin/admin &
node ./admin/admin-2/index.js &
echo 'http://localhost:3000'
echo 'http://localhost:3001'
