const COUNT = 100000;
let results = new Array (COUNT);

for (let i = 0 ; i < COUNT ; i ++) {
    results [i] = Date.now ();
}

console.log ('index,time');
for (let i = 0 ; i < COUNT ; i ++) {
    console.log ('%i,%f', i, results [i]);
}
