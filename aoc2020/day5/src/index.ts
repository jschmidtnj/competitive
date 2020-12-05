#!/usr/bin/env node
import { readFileSync } from 'fs';
import { initializeLogger } from './utils';
import { getLogger } from 'log4js';

const logger = getLogger();

const binarySearch = (input: string, searchSpace: number, lowerHalf: string, upperHalf: string): number => {
  let lowerBound = 0, upperBound: number = searchSpace - 1;
  for (const currentChar of input.substr(0, input.length - 1)) {
    // logger.info(`considering ${lowerBound} to ${upperBound}`);
    const delta = Math.ceil((upperBound - lowerBound) / 2);
    switch (currentChar) {
      case lowerHalf:
        upperBound -= delta;
        break;
      case upperHalf:
        lowerBound += delta;
        break;
      default:
        throw new Error(`invalid char found: ${currentChar}`);
    }
  }
  return input[input.length - 1] === lowerHalf ? lowerBound : upperBound;
};

const main = (): void => {
  const inputData = readFileSync('./input.txt', 'utf-8');
  const boardingPassLength = 10;
  const numRows = 128, numColumns = 8;
  let maxID = 0;
  let allIDs: number[] = [];
  for (const boardingPass of inputData.split('\n')) {
    if (boardingPass.length !== boardingPassLength) {
      continue;
    }
    const row = binarySearch(boardingPass.substr(0, 7), numRows, 'F', 'B');
    const col = binarySearch(boardingPass.substr(7), numColumns, 'L', 'R');
    const id = row * numColumns + col;
    allIDs.push(id);
    if (id > maxID) {
      maxID = id;
    }
  }
  logger.info(`part 1: ${maxID}`);
  allIDs = allIDs.sort();
  let seatID: number | null = null;
  for (let i = 0; i < allIDs.length - 1; i++) {
    if (allIDs[i + 1] - allIDs[i] === 2) {
      seatID = allIDs[i] + 1;
      break;
    }
  }
  if (seatID === null) {
    throw new Error('cannot find seat id');
  }
  logger.info(`part 2: ${seatID}`);
};

if (require.main === module) {
  const logger = initializeLogger();
  try {
    main();
  } catch (err) {
    logger.error((err as Error).message);
  }
}

export default main;
