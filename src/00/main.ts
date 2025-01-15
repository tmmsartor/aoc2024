import assert from 'assert';
import * as path from 'path';

import {read, ParsedData, get_day, Result} from '../utils';
import {sol1_test_true,sol2_test_true} from './solutions';

interface ParsedData1 {
	day: number
}

async function parse(input:ParsedData): Promise<ParsedData1> {
	try {
		var {lines, text, nrow, ncol} = input; 
		const day: number =  0; 
		return {day}
	} catch (error) {
		throw error;
	}
}

async function solve1(input: ParsedData1): Promise<number> {
	let res:number = 0;
	const { day } = input;
	console.log(`solve 1: ${day}`);
	// TODO
	return res;
}

async function solve2(input: ParsedData1): Promise<number> {
	let res:number = 0;
	const { day } = input;
	console.log(`solve 2: ${day}`);
	// TODO
	return res;
}

async function main() {
	try {
		const dirPath = __dirname.replace("dist","src");
		const input : ParsedData = await read(path.join(dirPath, 'input'));
		const input_test : ParsedData = await read(path.join(dirPath, 'input_test'));
		var sol1,sol2: number = 0;

		let sol1_test: number = await solve1(await parse(input_test));
		assert(sol1_test==sol1_test_true, `Test1 ${sol1_test} != ${sol1_test_true}`);
		sol1 = await solve1(await parse(input));

		let sol2_test: number = await solve2(await parse(input_test));
		assert(sol2_test==sol2_test_true, `Test2 ${sol2_test} != ${sol2_test_true}`);
		sol2 = await solve2(await parse(input));

		return {sol1, sol2};
	} catch (error) {
		if (error instanceof Error) {
			throw new Error(`Failed to Solve: ${error.message}`);
		}
		throw error;
	}
}

if (require.main === module) {
	get_day(__dirname).then((day:number) => console.log(`Day ${day}`));
	main().then((res:Result) => console.log(res.sol1,res.sol2));
}

export {main};
