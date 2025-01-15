import * as fs from 'fs/promises';
import path from 'path';

export interface ParsedData {
	lines: string[]
	text: string
	nrow: number
	ncol: number
}

export interface Result {
	sol1: number
	sol2: number
}

export interface Module {
	main: () => Promise<Result>;
}

async function read(filePath: string): Promise<ParsedData> {
	try {
		// Read the file content
		const fileContent = await fs.readFile(filePath, 'utf-8');
		const lines:string[] = [];
		var ncol: number = 1;
		var nrow: number = 0;
		var text: string = "";

		//.filter((line:string) => line.trim() !== '')
		fileContent
			.split('\n')
			.map((line:string, idx:number) => {
				if (!idx) ncol=line.length;
				nrow += 1;
				text+=line;
				lines.push(line);
		});
		return {lines,text, nrow, ncol};
	} catch (error) {
		throw error;
	}
}

async function get_day(filePath: string): Promise<number> {
	return parseInt(path.basename(filePath));
}

export {read, get_day};
