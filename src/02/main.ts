import * as path from 'path';
import * as fs from 'fs/promises';


let DEBUG = 0;

import {Result} from '../utils';


interface ParsedData {
		levels: number[][];
}

async function parse(filePath: string): Promise<ParsedData> {
		try {
			// Read the file content
			const fileContent = await fs.readFile(filePath, 'utf-8');

			const levels: number[][] = [];

			// Split content into lines and parse each line
			fileContent
				.split('\n')
				.filter((line:string) => line.trim() !== '') // Remove empty lines
				.map((line:string) => {
						const reports: number[] = line
							.trim()
							.split(/\s+/)
							.map(num => parseInt(num, 10));
						levels.push(reports);
			});
			return { levels };
		} catch (error) {
			if (error instanceof Error) {
				throw new Error(`Failed to parse file`);
			}
			throw error;
		}
}

async function solve1(input: ParsedData): Promise<number> {
	const { levels } = input;
	let res: number = 0;
	levels.forEach((reports:number[])=>{
		let is_valid = true;
		reports.slice(0,-1).forEach((r1:number,i:number) => {
			if (is_valid) {
				let r2:number = reports[i+1];
				if (Math.abs(r2-r1) > 3) {is_valid=false;}
				if (r2-r1 == 0) {is_valid=false;}
				if (r2>r1 && reports[1]<reports[0]) {is_valid=false;}
				if (r2<r1 && reports[0]<reports[1]) {is_valid=false;}
			}
		});
		if (is_valid) {res+=1;}
	});
	return res;
}

function increasing(reports: number[]):boolean {
		let up: number = 0;
		let down: number = 0;
		reports.slice(0,-1).forEach((r1:number,i:number) => {
			let r2:number = reports[i+1];
			if (r1-r2 < 0) up++;
			if (r1-r2 > 0) down++;
		});
		return (up>down)
}

function check(reports: number[]): number {
		let is_incr: boolean = increasing(reports);
		let is_safe: boolean = true;
		let idx: number = 0;
		reports.slice(0,-1).forEach((r1:number,i:number) => {
			if (is_safe){
				let r2:number = reports[i+1];
				if (Math.abs(r2-r1) > 3) {is_safe=false; idx = i;}
				else if (r2-r1 == 0) {is_safe=false;idx = i;}
				else if (r2<r1 && is_incr) {is_safe=false;idx = i;}
				else if (r2>r1 && !is_incr) {is_safe=false;idx = i;}
			}
		});
		if (!is_safe) {
			return idx;
		}
		return -1;
}

async function solve2(input: ParsedData): Promise<number> {
	const { levels } = input;
	let res: number = 0;
	levels.forEach((reports:number[])=>{
		let idx:number = check(reports);
		if (idx <0) {
			res += 1;
			return;
		}
		let reports0 = reports.slice();
		if (DEBUG) console.log(idx, reports);
		reports0.splice(idx,1);
		reports.splice(idx+1,1);
		if (DEBUG) console.log(reports,reports0)
		if (check(reports)<0 || check(reports0)<0) res+=1;
	});
	return res;
}

async function main() {
	try {
		const dirPath = __dirname.replace("dist","data");
		const input_path : string = path.join(dirPath, 'user1', 'input');
		//const sol : ParsedData = await read(path.join(dirPath, 'user1', 'sol'));

		//const input_test : ParsedData = await read(path.join(dirPath, 'test', 'input'));
		//const sol_test : ParsedData = await read(path.join(dirPath, 'test', 'sol'));

		//const sol1_test: number = await solve(await parse(input_test));
		//assert(sol1_test==sol1_test_true, `Test1 ${sol1_test} != ${sol1_test_true}`);

		let sol1 :number = await solve1(await parse(input_path));

		//const sol2_test: number = await solve(await parse(input_test, {part2: true}));
		//assert(sol2_test==sol2_test_true, `Test2 ${sol2_test} != ${sol2_test_true}`);
		let sol2 :number = await solve2(await parse(input_path));


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
