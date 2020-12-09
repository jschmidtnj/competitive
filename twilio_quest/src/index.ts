#!/usr/bin/env node
import { initializeLogger } from './utils';
import { getLogger } from 'log4js';
import http from 'http';

const logger = getLogger();

const PORT = 8080;

const main = (): void => {
  const app = http.createServer((_req, res) => {
    res.end('hello world!');
  });
  app.listen(PORT, () => {
    logger.info(`twilio listening on port http://localhost:${PORT} 🚀`);
  });
};

if (require.main === module) {
  initializeLogger();
  try {
    main();
  } catch (err) {
    logger.error((err as Error).message);
  }
}

export default main;
