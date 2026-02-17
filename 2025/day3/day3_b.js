import fs from 'node:fs';

function find_max(line, start, to_leave) {
  let max_digit = 0;
  let max_idx;
  for (let j = start; j < line.length - to_leave; j++) {
    if (line[j] > max_digit) {
      max_digit = line[j];
      max_idx = j;
    } 
  } 
  return [max_digit, max_idx];
}

try {
  const data = fs.readFileSync('./input', 'utf8');
  const lines = data.split('\n');
  let total_joltage = 0;
  for (let i = 0; i < lines.length - 1; i++) {
    const line = lines[i];
    let start = 0;
    let j = 12;
    while (j--) {
      let [dig, tmp] = find_max(line, start, j);
      total_joltage += parseInt(dig * (10 ** j));
      start = tmp + 1;
    } 
  }
  console.log(total_joltage)
} catch (err) {
  console.error(err);
}
