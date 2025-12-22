import fs from 'node:fs';

try {
  const data = fs.readFileSync('./input', 'utf8');
  const lines = data.split('\n');
  let total_joltage = 0;
  for (let i = 0; i < lines.length - 1; i++) {
    const line = lines[i];
    let max_digit = 0;
    let max_idx;
    for (let j = 0; j < line.length - 1; j++) {
      if (line[j] > max_digit) {
        max_digit = line[j];
        max_idx = j;
      } 
    } 
    total_joltage += parseInt(max_digit * 10);
    max_digit = 0;
    for (let j = max_idx + 1; j < line.length; j++) {
      if (line[j] > max_digit) {
        max_digit = line[j];
      } 
    }
    total_joltage += parseInt(max_digit);
  }
  console.log(total_joltage)
} catch (err) {
  console.error(err);
}
