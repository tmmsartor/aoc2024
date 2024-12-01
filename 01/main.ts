import * as fs from 'fs/promises';

interface ParsedNumbers {
		firstNumbers: number[];
		secondNumbers: number[];
}

async function parse(filePath: string): Promise<ParsedNumbers> {
		try {
			// Read the file content
			const fileContent = await fs.readFile(filePath, 'utf-8');

			const firstNumbers: number[] = [];
			const secondNumbers: number[] = [];

			// Split content into lines and parse each line
			fileContent
				.split('\n')
				.filter((line:string) => line.trim() !== '') // Remove empty lines
				.map((line:string) => {
						const [first, second] = line
							.trim()
							.split(/\s+/)
							.map(num => parseInt(num, 10));
						if (isNaN(first) || isNaN(second)) {
								throw new Error(`Invalid number pair in line: ${line}`);
						}
						firstNumbers.push(first);
						secondNumbers.push(second);
			});
			return { firstNumbers, secondNumbers };
		} catch (error) {
			if (error instanceof Error) {
				throw new Error(`Failed to parse file: ${error.message}`);
			}
			throw error;
		}
}

async function solve1(input: ParsedNumbers): Promise<number> {
	const {firstNumbers, secondNumbers } = input;
	firstNumbers.sort((a, b) => a - b);
	secondNumbers.sort((a, b) => a - b);
	let sum:number = 0;
	firstNumbers.forEach((num:number, index:number) => {
		sum += Math.abs(num - secondNumbers[index]);
	});
	return sum;
}

async function solve2(input: ParsedNumbers): Promise<number> {
	const {firstNumbers, secondNumbers } = input;
	let score:number = 0;
	const occurrences = new Map<number, number>();

	secondNumbers.forEach(num => {
		occurrences.set(num, (occurrences.get(num) || 0) + 1);
	});

	firstNumbers.forEach((num:number) => {
		score += num *  (occurrences.get(num) || 0)
	});

	return score;
}

// Example usage
async function main() {
	try {
		const input : ParsedNumbers = await parse('input');

		console.log(await solve1(input));
		console.log(await solve2(input));


	} catch (error) {
			console.error('Error:', error.message);
			process.exit(1);
	}
}

main();
