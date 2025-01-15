//import assert from 'assert';
import * as path from 'path';

import {read, ParsedData, get_day, Result} from '../utils';

interface ParsedData1 {
	pairs: number[][]
}

interface RegexMatch {
    fullMatch: string;
    groups: string[];
    start: number;
    end: number;
}


async function parse(input: ParsedData, {part2 = false}: {part2?: boolean} = {}): Promise<ParsedData1> {
	try {
		const {lines, text, ncol, nrow} = input;
		const pairs: number[][] = [];
		const regex = new RegExp(/mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\)/g);
		var match: RegExpExecArray | null;
		let enabled: boolean = true;

		lines.forEach((line:string) => { 
			while ((match = regex.exec(line)) !== null) {
				if (match[0] == "do()") {enabled = true; continue;}
				if (match[0] == "don't()") {enabled = false; continue;}
				if (match[0].slice(0,3)=="mul" && (!part2 || enabled)) {
					const pair: number[] = match.slice(1).map((num:string) => {return parseInt(num)});
					pairs.push(pair);
				}
			}
		});
		return {pairs};
	} catch (error) {
		throw error;
	}
}

async function solve(input: ParsedData1): Promise<number> {
	let res:number = 0;
	const { pairs } = input;
	pairs.forEach((pair:number[]) => {res += pair[0]*pair[1]});
	return res;
}

async function main() {
	try {
		const dirPath = __dirname.replace("dist","data");
		const input : ParsedData = await read(path.join(dirPath, 'user1', 'input'));
		//const sol : ParsedData = await read(path.join(dirPath, 'user1', 'sol'));

		//const input_test : ParsedData = await read(path.join(dirPath, 'test', 'input'));
		//const sol_test : ParsedData = await read(path.join(dirPath, 'test', 'sol'));

		//const sol1_test: number = await solve(await parse(input_test));
		//assert(sol1_test==sol1_test_true, `Test1 ${sol1_test} != ${sol1_test_true}`);

		let sol1 :number = await solve(await parse(input));

		//const sol2_test: number = await solve(await parse(input_test, {part2: true}));
		//assert(sol2_test==sol2_test_true, `Test2 ${sol2_test} != ${sol2_test_true}`);
		let sol2 :number = await solve(await parse(input, {part2: true}));


		return {sol1, sol2};
	} catch (error) {
		if (error instanceof Error) {
			throw new Error(`Failed to Solve: ${error.message}`);
		}
		throw error;
	}
}

if (require.main === module) {
	//get_day(__dirname).then((day:number) => console.log(`Day ${day}`));
	main().then((res:Result) => { console.log(res.sol1); console.log(res.sol2);});
}

export {main};
