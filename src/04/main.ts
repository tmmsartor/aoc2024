//import assert from 'assert';
import * as path from 'path';

import {read, ParsedData, get_day, Result} from '../utils';
//import {sol1_test_true,sol2_test_true} from './solutions';


interface ParsedData1 {
	rows: string[]
	columns: string[]
	diagonal1: string[]
	diagonal2: string[]
}

async function parse(input:ParsedData): Promise<ParsedData1> {
	try {
		var {lines, text, nrow, ncol} = input; 
		const rows: string[] = [];
		const columns: string[] = [];
		const diagonal1: string[] = [];
		const diagonal2: string[] = [];

		let i:number = 0;
		let j:number = 0;
		var buffer: string = "";

		// rows
		for (j=0; j<nrow; j++){
			rows.push(text.slice(j*ncol,(j+1)*ncol));
		}
		// columns
		for (j=0; j<nrow; j++){
			buffer = "";
			for (i=0; i<ncol; i++) buffer += text[i*ncol+j];
			columns.push(buffer);
		}
		// first diags
		for (i=0; i<(nrow-3); i++){
			buffer = "";
			j = i*ncol;
			while ( j < text.length && buffer.length<=Math.min(nrow-i,ncol)) {
				buffer += text[j];
				j += ncol+1;
			}
			diagonal1.push(buffer);
		}
		for (i=1; i<(ncol-3); i++){
			buffer = "";
			j = i;
			while ( j < text.length && buffer.length<=Math.min(ncol-i-1,nrow)) {
				buffer += text[j];
				j += ncol+1;
			}
			diagonal1.push(buffer);
		}
		// second diags
		for (i=nrow-1; i>=3; i--){
			buffer = "";
			j = i*ncol;
			while (j > 0 && buffer.length<=Math.min(i,ncol)) {
				buffer += text[j];
				j -= (ncol-1);
			}
			diagonal2.push(buffer);
		}
		for (i=1; i<(ncol-3); i++){
			buffer = "";
			j = (nrow-1)*ncol+i;
			while ( j > 0 && buffer.length<=Math.min(ncol-i-1,nrow)) {
				buffer += text[j];
				j -= (ncol-1);
			}
			diagonal2.push(buffer);
		}

		return {rows, columns, diagonal1, diagonal2};
	} catch (error) {
		throw error;
	}
}

async function solve1_a(input: ParsedData1): Promise<number> {
	// extract 'bands' of text in the allowe direction
	let res:number = 0;
	let res_temp:number = 0;
	const regex = new RegExp(/XMAS|SAMX/g);
	let match: RegExpExecArray | null;
	Object.entries(input).forEach(([key, value]) => {
		//console.log(`${key} ${value.length}`)
		value.forEach((line:string, idx:number) => {
			res_temp=0;
			while ((match = regex.exec(line)) !== null) {
				res_temp += 1
				regex.lastIndex = match.index + 1;
			};
			//console.log(`${key},${idx}:${line}:${res_temp}`);
			//console.log(`${key},${idx}:${line.length}:${res_temp}`);
			res += res_temp;
		});
	});
	return res;
}

async function solve2(input: ParsedData): Promise<number> {
	let res:number = 0;
	const {text,nrow,ncol} = input;
	var edges:string = "";
	var i,j: number = 0;
	var temp:string = "";
	for (i=1;i<ncol-1;i++){
		for (j=1;j<nrow-1;j++){
			if (text[i+j*ncol] != 'A') continue;
			edges =
				text[(i-1)+(j-1)*ncol]+
				text[(i-1)+(j+1)*ncol]+
				text[(i+1)+(j+1)*ncol]+
				text[(i+1)+(j-1)*ncol];
			edges += edges;
			for (let k=0;k<4;k++){
				temp = edges.slice(k,k+4);
				if (temp=="MMSS") res+=1
			}
		}
	}
	return res;
}

async function main() {
	try {
  	const dirPath = __dirname.replace("dist","data");
		const input : ParsedData = await read(path.join(dirPath, 'user1', 'input'));
		//const input_test : ParsedData = await read(path.join(dirPath, 'test', 'input'));

		//let sol1_test: number = await solve1_a(await parse(input_test));
		//assert(sol1_test==sol1_test_true, `Test1 ${sol1_test} != ${sol1_test_true}`);

		let sol1: number = await solve1_a(await parse(input));
		//console.log(sol1);

		//let sol2_test: number = await solve2(input_test);
		//assert(sol2_test==sol2_test_true, `Test2 ${sol2_test} != ${sol2_test_true}`);

		let sol2: number = await solve2(input);
		//console.log(sol2);

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
