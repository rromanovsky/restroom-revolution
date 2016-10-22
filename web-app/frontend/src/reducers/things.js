import actionTypes from '../actions/types/app';
import _ from 'lodash';

export default (state = {}, action) => {

  switch (action.type) {
    case actionTypes.GOT_DATA:
      var v = _.get(action, 'data.thing', '<undefined>');
      var newVar = {
        isBusy: _.get(action, 'data.isBusy', true)
      };

      console.log('...new values', v, newVar);

      return {
        ...state,
        [v]: newVar
      };

    default:
      return state

  }
}