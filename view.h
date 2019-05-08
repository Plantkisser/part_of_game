sf:: View coordiantesForView(Coordinate <float> crd, sf:: View* view)
{
	assert(view);
	view->setCenter(crd.x, crd.y);

	return *view;
}