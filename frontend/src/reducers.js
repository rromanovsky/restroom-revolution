import { combineReducers } from 'redux';
import users from './modules/users/reducers';
import jobs from './modules/jobs/reducers';

export default combineReducers({
  users,
  jobs,
});
