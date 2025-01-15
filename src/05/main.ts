import assert from 'assert';
import * as path from 'path';

import {read, ParsedData, get_day, Result} from '../utils';
//import {sol1_test_true,sol2_test_true} from './solutions';

interface Pair {
	f: number;
	s: number;
}

interface IndexMap {
	[key: number]: number;
}

interface RuleMap {
	[key: number]: number[];
}


interface ParsedData1 {
	rules: Pair[]
	rules_m: RuleMap
	updates: IndexMap[]
	updates_num: number[][]
}

async function parse(input:ParsedData): Promise<ParsedData1> {
	try {
		var {lines, text, nrow, ncol} = input; 
		let p2: boolean = false; 
		const rules: Pair[] = [];
		const rules_m: RuleMap = {};
		const updates: IndexMap[] = [];
		const updates_num: number[][] = [];
		lines.forEach((line:string) => {
			if (line == "")  p2 = true;
			else if (!p2) {
				const [f,s] = line.split("|").map((subs) => parseInt(subs));
				if (!rules_m[f]) rules_m[f] = [];
				rules_m[f].push(s);
				rules.push({f:f, s:s});
			} else {
				const update = line.split(",").map((subs) => parseInt(subs));
				updates_num.push(update);
				updates.push(Object.fromEntries(update.map((item, index) => [item, index])));
			}
		});
		return {rules, rules_m, updates, updates_num}

	} catch (error) {
		throw error;
	}
}

async function solve1(input: ParsedData1): Promise<number> {
	let res:number = 0;
	const { rules,rules_m,updates,updates_num } = input;
	const upn = updates_num;
	let valid: boolean = true;
	updates.forEach((up:IndexMap,idx)=>{
		valid = true;
		rules.forEach((rule) => {if (up[rule.f] > up[rule.s]) valid=false;})
		if (valid) res+=upn[idx][(upn[idx].length-1)/2];
	});
	return res;
}

function resolve(second:number, first:number, ups:number[], rules_m: RuleMap): number[] {
	const up: IndexMap = Object.fromEntries(ups.map((item, index) => [item, index]));
	let m_l:number = 0;
	let m_r:number = 0;
	let moving_i = up[second];
	while (up[second] < up[first]){
		moving_i+=1;
		m_r = ups[moving_i];
		while (up[m_r] >  up[second]) {
			m_l = ups[up[m_r]-1];
			if (!rules_m[m_l] || !rules_m[m_l].includes(m_r)) {
				// move
				up[m_r] -= 1;
				up[m_l] += 1;
				ups[up[m_r]] = m_r;
				ups[up[m_l]] = m_l;
				m_l = ups[up[m_r]-1];
			} else break;
		}
	}
	return ups;
}


async function solve2(input: ParsedData1): Promise<number> {
	let res:number = 0;
	let ups:number[] = [];
	const { rules,rules_m,updates,updates_num } = input;
	let invalid: boolean = false;
	updates.forEach((up:IndexMap,idx:number)=>{
		ups = updates_num[idx];
		invalid = false;
		rules.forEach((rule) => {
			if (up[rule.f] > up[rule.s]) {
				invalid = true;
				ups = resolve(rule.s, rule.f, ups, rules_m);
				up = Object.fromEntries(ups.map((item, index) => [item, index]));
			}
		});
		if (invalid) res+=ups[(ups.length-1)/2];
	});
	return res;
}

async function main() {
	try {
		const dirPath = __dirname.replace("dist","data");
		const input : ParsedData = await read(path.join(dirPath, 'user1', 'input'));
		//const input_test : ParsedData = await read(path.join(dirPath, 'test', 'input'));
		var sol1: number = 0;
		var sol2: number = 0;

		//let sol1_test: number = await solve1(await parse(input_test));
		//assert(sol1_test==sol1_test_true, `Test1 ${sol1_test} != ${sol1_test_true}`);
		sol1 = await solve1(await parse(input));

		//let sol2_test: number = await solve2(await parse(input_test));
		//assert(sol2_test==sol2_test_true, `Test2 ${sol2_test} != ${sol2_test_true}`);
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
	//get_day(__dirname).then((day:number) => console.log(`Day ${day}`));
	main().then((res:Result) => { console.log(res.sol1); console.log(res.sol2);});
}

export {main};
